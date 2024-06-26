#include <QtGui>
#include "recargabilletera.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QIntValidator>
#include <stdio.h>
#include "dialog/dialog.h"
#include "sessionmanager.h"
#include <QVariantMap>
#include <QStringList>

RecargaBilleteraScreen::RecargaBilleteraScreen(QWidget *parent)
    : QWidget(parent)
{
    // Icono en la parte izquierda de la pantalla
    QLabel *iconLabel = new QLabel;
    QPixmap iconPixmap(":/assets/icons/wallet.png");
    iconPixmap = iconPixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio);
    iconLabel->setPixmap(iconPixmap);
    iconLabel->setStyleSheet("margin-top: -130px;");

    // Barra en el medio
    QLabel *barLabel = new QLabel;
    QPixmap barPixmap(":/assets/icons/div.png"); // Reemplaza ":/assets/bar.png" con la ruta a tu barra
    barLabel->setPixmap(barPixmap);
    barLabel->setStyleSheet("margin-right: 12px;");

    // Título centrado
    QLabel *titleLabel = new QLabel("Recarga Billetera");
    titleLabel->setFont(QFont("Arial", 14, QFont::Bold));
    titleLabel->setFixedWidth(150); // Ajusta el ancho según sea necesario
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    titleLabel->setWordWrap(true); // Permitir el ajuste de línea automático si el texto es demasiado largo

    // Inputs de texto

    nameLine = new QLineEdit("5555874201"); // Inicializa nameLine y asígnalo a la variable miembro
    // QLineEdit *nameLine = new QLineEdit("5555874201"); // Sin valor inicial
    nameLine->setPlaceholderText("Ingrese el documento del usuario");
    nameLine->setStyleSheet("border: 1px solid black; border-radius: 4px; font-size: 14pt;");
    nameLine->setFixedWidth(150);
    nameLine->setFixedHeight(40);
    nameLine->setFocus();

    // Configurar un validador para permitir solo valores numéricos
    QIntValidator *validator = new QIntValidator(nameLine);
    nameLine->setValidator(validator);

    modifyingText = "";

    addressText = new QLineEdit("2,000 COP"); // Inicializa addressText y asígnalo a la variable miembro

    // QLineEdit *addressText = new QLineEdit("20.000 COP");
    addressText->setPlaceholderText("Ingrese el valor de su recarga");
    addressText->setStyleSheet("border: 1px solid black; border-radius: 4px; font-size: 14pt;");
    addressText->setFixedWidth(150);
    addressText->setFixedHeight(40);

    // Botón de envío
    QPushButton *submitButton = new QPushButton();
    QIcon submitIcon(":/assets/icons/check_ok.png");
    submitButton->setIcon(submitIcon);
    submitButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    // addButton->setStyleSheet("border: 2px solid black; background-color: white;");
    submitButton->setStyleSheet("border: none");

    resultLabel = new QLabel;

    // Crear el QLabel para el texto de información
    infoText = new QLabel("Ingresa el documento del usuario para continuar", this);
    infoText->setFont(QFont("Arial", 14));

    // Establece un ancho máximo
    int maxWidth = 300;
    infoText->setMaximumWidth(maxWidth);

    // Permite que el texto se envuelva
    infoText->setWordWrap(true);

    // Crear el QLabel para el texto "saldo actual"
    saldoLabel = new QLabel("SALDO ACTUAL:", this);
    saldoLabel->setFont(QFont("Arial", 14));
    saldoLabel->setVisible(false);
    saldoLabel->setMaximumWidth(600);
    saldoLabel->setWordWrap(true);

    // Crear el QLabel para el valor 1000
    valorLabel = new QLabel("1000", this);
    valorLabel->setVisible(false);
    valorLabel->setMaximumWidth(maxWidth);
    valorLabel->setWordWrap(true);

    // Crear el QLabel para el texto "saldo nuevo"
    saldoNuevoLabel = new QLabel("SALDO NUEVO:", this);
    saldoNuevoLabel->setStyleSheet("QLabel { color : green; }");
    saldoNuevoLabel->setVisible(false);
    saldoNuevoLabel->setMaximumWidth(maxWidth);
    saldoNuevoLabel->setWordWrap(true);

    // Crear el QLabel para el nuevo valor
    valorNuevoLabel = new QLabel("2000", this); // Ejemplo de nuevo valor
    valorNuevoLabel->setVisible(false);
    valorNuevoLabel->setMaximumWidth(maxWidth);
    valorNuevoLabel->setWordWrap(true);

    // Layout principal
    QGridLayout *mainLayout = new QGridLayout;

    // Agregar elementos al layout
    mainLayout->addWidget(iconLabel, 0, 0, 4, 1, Qt::AlignLeft);  // Icono en la esquina superior izquierda
    mainLayout->addWidget(barLabel, 0, 1, 4, 1, Qt::AlignCenter); // Barra en el medio
    mainLayout->addWidget(titleLabel, 0, 2, 1, 2, Qt::AlignLeft); // Título centrado horizontalmente
    mainLayout->addWidget(nameLine, 1, 2, 1, 1, Qt::AlignRight);  // Primer input a la derecha

    mainLayout->addWidget(addressText, 2, 2, 1, 1, Qt::AlignRight); // Segundo input a la derecha
    mainLayout->addWidget(infoText, 3, 2, 1, 1, Qt::AlignCenter);   // Botón centrado debajo de los inputs
    mainLayout->addWidget(saldoLabel, 3, 2, 1, 1, Qt::AlignLeft);   // Botón centrado debajo de los inputs
    mainLayout->addWidget(valorLabel, 3, 3, 1, 1, Qt::AlignCenter); // Botón centrado debajo de los inputs

    mainLayout->addWidget(saldoNuevoLabel, 4, 2, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(valorNuevoLabel, 4, 3, 1, 1, Qt::AlignCenter);

    setLayout(mainLayout);

    // Fullscreen
    setWindowState(windowState() ^ Qt::WindowFullScreen);

    // Signals and Slots (Events)

    // En el constructor de AddressBook en addressbook.cpp
    connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmit()));

    // Conecta el evento de teclado al QLineEdit
    connect(nameLine, SIGNAL(textChanged(const QString &)), this, SLOT(handleTextChanged(const QString &)));

    /*
        Obtener el balance actual de la tarjeta del usuario con el evento
        textChange del input nameLine que corresponde al número de documento
        del usuario
    */
    // Convertir la cadena JSON en un objeto JSON
    connect(nameLine, SIGNAL(textChanged(const QString &)), this, SLOT(getCurrentBalance(const QString &)));

    // Conectar la función de validación al evento textChanged del QLineEdit
    connect(addressText, SIGNAL(textChanged(const QString &)), this, SLOT(validateAddressText(const QString &)));
}

void RecargaBilleteraScreen::handleSubmit()
{
    //    emit loginSuccessful();
    qDebug() << "Probando recarga de billetera" << "Estamo activos";
}

// Función para manejar el cambio de texto en el QLineEdit
void RecargaBilleteraScreen::handleTextChanged(const QString &text)
{
    // Realizar acciones en respuesta al cambio de texto
    qDebug() << "Texto cambiado:" << text;
    // Puedes realizar cualquier acción adicional que desees con el texto cambiado, como actualizar otras partes de la interfaz de usuario o realizar alguna lógica de validación.
}

QVariantMap RecargaBilleteraScreen::stringToJson(const QString &jsonString)
{
    QVariantMap jsonMap;

    // Remover los primeros y últimos caracteres, que son '{' y '}'
    QString cleanedString = jsonString.mid(1, jsonString.size() - 2);

    // Separa la cadena en pares de clave-valor utilizando el delimitador ","
    QStringList keyValuePairs = cleanedString.split(",");

    // Itera sobre los pares de clave-valor
    foreach (const QString &pair, keyValuePairs)
    {
        // Separa cada par de clave-valor utilizando el delimitador ":"
        QStringList keyValue = pair.split(":");

        // Asegúrate de que haya un par de clave-valor válido
        if (keyValue.size() == 2)
        {
            // Extrae la clave y el valor
            QString key = keyValue[0].trimmed();
            QString value = keyValue[1].trimmed();

            // Quita las comillas alrededor de la clave y el valor
            key.remove(0, 1);
            key.remove(key.size() - 1, 1);
            value.remove(0, 1);
            value.remove(value.size() - 1, 1);

            // Agrega el par de clave-valor al mapa JSON
            jsonMap[key] = value;
        }
    }

    return jsonMap;
}

QVariantMap RecargaBilleteraScreen::parseJsonObject(const QString &jsonString)
{
    QVariantMap jsonMap;
    QRegExp rx("\"([^\"]*)\"\\s*:\\s*([^,\\{\\}\\[\\]]+|\\{[^\\}]*\\}|\\[[^\\]]*\\])");
    int pos = 0;

    while ((pos = rx.indexIn(jsonString, pos)) != -1)
    {
        QString key = rx.cap(1);
        QString value = rx.cap(2);

        jsonMap[key] = parseJsonValue(value);

        pos += rx.matchedLength();
    }

    return jsonMap;
}

QVariant RecargaBilleteraScreen::parseJsonValue(const QString &jsonString)
{
    if (jsonString.startsWith('{'))
    {
        return parseJsonObject(jsonString);
    }
    else if (jsonString.startsWith('['))
    {
        return parseJsonArray(jsonString);
    }
    else if (jsonString == "true")
    {
        return true;
    }
    else if (jsonString == "false")
    {
        return false;
    }
    else if (jsonString == "null")
    {
        return QVariant();
    }
    else if (jsonString.startsWith('"'))
    {
        return jsonString.mid(1, jsonString.length() - 2); // Remove quotes
    }
    else
    {
        bool ok;
        int intValue = jsonString.toInt(&ok);
        if (ok)
        {
            return intValue;
        }
        double doubleValue = jsonString.toDouble(&ok);
        if (ok)
        {
            return doubleValue;
        }
    }
    return jsonString; // As fallback
}

QVariantList RecargaBilleteraScreen::parseJsonArray(const QString &jsonString)
{
    QVariantList jsonArray;
    QRegExp rx("([^,\\[\\]\\{\\}]+|\\{[^\\}]*\\}|\\[[^\\]]*\\])");
    int pos = 1; // Skip the initial '['

    while ((pos = rx.indexIn(jsonString, pos)) != -1)
    {
        QString value = rx.cap(1);
        jsonArray.append(parseJsonValue(value));

        pos += rx.matchedLength();
    }

    return jsonArray;
}

void RecargaBilleteraScreen::getCurrentBalance(const QString &text)
{

    // Validar que la longitud del texto sea de 10 dígitos
    if (text.length() == 10 && text.toInt() != 0) // Asegúrate de que es un número válido
    {
        qDebug() << "Longitud válida de 10 dígitos.";
        QString jwtToken = SessionManager::instance().getJwtToken();

        // Obtener el valor de nameLine como el documento
        QString document = nameLine->text();

        qDebug() << "User Document." << document;
        SessionManager::instance().setCurrentUserDocument(document);

        // Convertir jwtToken a un objeto JSON utilizando stringToJson
        QVariantMap jwtTokenJson = stringToJson(jwtToken);
        QString accessToken = jwtTokenJson.value("access_token").toString();

        qDebug()
            << "jwt." << jwtToken;
        qDebug() << "jwtTokenJson" << jwtTokenJson;
        qDebug() << "accessToken" << accessToken;

        // Crear la URL con el parámetro document
        QString url = QString("https://fleet.nebulae.com.co/api/external-network-gateway/rest/endUser/findByDocument?documentType=CITIZENSHIP_CARD&document=%1").arg(document);

        // Crear el manager de la red
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        // Conectar la señal de respuesta usando la sintaxis antigua
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleNetworkReply(QNetworkReply *)));

        // Crear la solicitud HTTP
        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
        request.setRawHeader("Accept", "application/json"); // Especificar que esperas una respuesta JSON

        // Enviar la solicitud
        manager->get(request);
    }
    else
    {
        qDebug() << "Longitud inválida, debe ser de 10 dígitos.";
    }
}

void RecargaBilleteraScreen::updateSaldoLabel(int balance, const QString &response)
{
    // Crear el texto con HTML para estilizar el balance en rojo
    QLocale locale = QLocale::system();
    QString formattedBalance = locale.toString(balance);
    QString text = QString("");
    // Iniciar un temporizador de 5 segundos para restablecer el contenido inicial de saldoText
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(restoreSaldoLabel()));

    if (balance < 0)
        text = QString("SALDO ACTUAL: <span style='color:red;'>%1 COP</span>").arg(formattedBalance);
    else if (response != "no")
    {
        text = QString("<span style='color:red;'>%1</span>").arg(response);
        timer->start(5000);
    }
    else
        text = QString("SALDO ACTUAL: %1 COP").arg(formattedBalance);

    infoText->setVisible(false);
    saldoLabel->setVisible(true);
    saldoLabel->setText(text);
}

void RecargaBilleteraScreen::restoreSaldoLabel()
{
    infoText->setVisible(true);
    saldoLabel->setVisible(false);
}

void RecargaBilleteraScreen::handleNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // Leer la respuesta
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;

        // Asignar la respuesta a la variable currentBalance
        currentBalance = QString(responseData);

        QVariantMap balanceJsonMap = parseJsonObject(currentBalance);
        if (balanceJsonMap.contains("fullName"))
            userName = balanceJsonMap["fullName"].toString();
        userDocument = nameLine->text();

        if (balanceJsonMap.contains("id"))
        {
            userId = balanceJsonMap["id"].toString();
            SessionManager::instance().setCurrentUserId(userId);
        }

        if (balanceJsonMap.contains("wallet"))
        {
            QVariantMap wallet = balanceJsonMap["wallet"].toMap();
            if (wallet.contains("pockets"))
            {
                QVariantMap pockets = wallet["pockets"].toMap();
                if (pockets.contains("REGULAR"))
                {
                    QVariantMap regularPocket = pockets["REGULAR"].toMap();
                    if (regularPocket.contains("balance"))
                    {
                        int balance = regularPocket["balance"].toInt();
                        qDebug() << "Balance: " << balance;
                        QString response = QString("no");
                        QMetaObject::invokeMethod(this, "updateSaldoLabel", Q_ARG(int, balance), Q_ARG(const QString &, response));
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QString response = QString("Error al obtener el saldo de este usuario");
        int balance = 666;
        QMetaObject::invokeMethod(this, "updateSaldoLabel", Q_ARG(int, balance), Q_ARG(const QString &, response));
    }

    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

void RecargaBilleteraScreen::validateAddressText(const QString &text)
{
    QString modifiedText;

    // Eliminar caracteres no deseados del texto (permitir solo números, un punto decimal y el sufijo "COP")
    for (int i = 0; i < text.size(); ++i)
    {
        QChar ch = text.at(i);
        if (ch.isDigit() || ch == '.' || (ch == ' ' && text.mid(i) == " COP"))
        {
            modifiedText.append(ch);
        }
    }

    // Verificar si el sufijo "COP" está presente al final del texto
    if (!modifiedText.endsWith(" COP"))
    {
        modifiedText += " COP";
    }

    // Formatear el número con coma para las milesimas si es necesario
    QString amount = modifiedText.left(modifiedText.indexOf(" COP"));
    QString formattedAmount;
    int value = amount.toInt();
    if (value >= 1000)
    {
        formattedAmount = QString::number(value);

        // Insertar comas cada 1.000 unidades
        int separatorPos = formattedAmount.length() % 3;
        if (separatorPos == 0)
        {
            separatorPos = 3;
        }
        while (separatorPos < formattedAmount.length())
        {
            formattedAmount.insert(separatorPos, ',');
            separatorPos += 4; // Moverse cuatro caracteres para llegar al siguiente grupo de tres dígitos
        }
    }
    else
    {
        formattedAmount = amount;
    }

    // Reemplazar el texto original con el texto formateado
    modifiedText.replace(0, modifiedText.indexOf(" COP"), formattedAmount);

    // Verificar la posición del cursor y ajustarla si es necesario
    int cursorPosition = addressText->cursorPosition();
    int formattedAmountLength = formattedAmount.length();
    if (cursorPosition < formattedAmountLength)
    {
        // Si el cursor está dentro del texto formateado, ajustar la posición del cursor en el texto original
        int commaCount = formattedAmount.count(',');
        int originalCursorPosition = cursorPosition - commaCount; // Ajustar la posición del cursor considerando las comas
        int originalTextLength = amount.length();
        if (originalCursorPosition < originalTextLength)
        {
            // Si el cursor está dentro del texto original, ajustar la posición del cursor en el texto modificado
            int commaCountInOriginal = amount.left(originalCursorPosition).count(',');
            cursorPosition = originalCursorPosition + commaCountInOriginal;
        }
        else
        {
            // Si el cursor está después del texto original, ajustar la posición del cursor en el sufijo "COP"
            cursorPosition = modifiedText.indexOf(" COP");
        }
    }
    else
    {
        // Si el cursor está después del texto formateado, ajustar la posición del cursor en el sufijo "COP"
        cursorPosition = modifiedText.indexOf(" COP");
    }

    // Actualizar el texto y la posición del cursor en el QLineEdit
    addressText->blockSignals(true); // Bloquea las señales para evitar la recursión
    addressText->setText(modifiedText);
    addressText->setCursorPosition(cursorPosition);
    addressText->blockSignals(false); // Desbloquea las señales
}

QString RecargaBilleteraScreen::extractNumericValue(const QString &text)
{
    QString result = text;

    // Eliminar el sufijo "COP"
    result.replace("COP", "", Qt::CaseInsensitive);

    // Eliminar comas
    result.remove(',');

    // Eliminar puntos decimales
    result.remove('.');

    // Eliminar espacios en blanco
    result = result.trimmed();

    return result;
}

void RecargaBilleteraScreen::executeSale(const QString &)
{
}

int RecargaBilleteraScreen::removeCommasAndConvertToInt(const QString &priceString)
{
    // Remover las comas del string
    QString priceWithoutCommas = priceString;
    priceWithoutCommas.remove(',');

    // Convertir el string a un entero
    bool ok;
    int price = priceWithoutCommas.toInt(&ok);

    // Verificar si la conversión fue exitosa
    if (!ok)
    {
        qWarning() << "Error: No se pudo convertir el string a un entero";
        // En este caso, podrías devolver un valor predeterminado o lanzar una excepción
    }

    return price;
}

void RecargaBilleteraScreen::keyPressEvent(QKeyEvent *event)
{
    QLineEdit *currentLineEdit = dynamic_cast<QLineEdit *>(focusWidget());
    QString text = currentLineEdit->text();
    int cursorPosition = currentLineEdit->cursorPosition();

    switch (event->key())
    {
    case Qt::Key_Return:
    {
        // Crear una instancia del diálogo de respuesta del servidor
        ResponseDialog *responseDialog = new ResponseDialog();

        // Configurar el icono de respuesta en el dialogo
        QIcon responseIcon(":/assets/icons/dialog/alert.png");
        responseDialog->setResponseIcon(responseIcon);

        // Configurar el texto de respuesta en el diálogo
        responseDialog->setResponseText("Confirmar venta", "yes");

        // Eliminar sufijo COP y espacios en blanco addressText antes de mostrar el mensaje
        QString saleAmmount = addressText->text();

        // Eliminar el sufijo "COP"
        saleAmmount.replace("COP", "", Qt::CaseInsensitive);

        // Eliminar espacios en blanco
        saleAmmount = saleAmmount.trimmed();

        // revisar variable que contiene el valor deseado para la recarga
        qDebug() << "removeCommasAndConvertToInt + saleAmmount" << removeCommasAndConvertToInt(saleAmmount);

        // Valor de la venta en el singleton
        SessionManager::instance().setCurrentUnitPrice(removeCommasAndConvertToInt(saleAmmount));

        // Agregar texto adicional con información sobre la venta
        QString additionalText = QString("Producto: Recarga Billetera\n") +
                                 QString("Usuario: " + userName + "\n") +
                                 QString("Documento: " + userDocument + "\n") +
                                 QString("Valor: ") + saleAmmount + " COP";

        responseDialog->setAdditionalText(additionalText);

        // Configurar el texto de respuesta para el botón en el diálogo
        responseDialog->setCloseButtonText("Confirmar");

        responseDialog->setCancelButtonText("Cancelar");

        /*
            Conectar la señal 'saleSuccess()' de responseDialog al slot 'emitSaleSuccessToMainWindow()'
            que emite la señal 'showSaleScreen()' en MainWindow.

        */
        connect(responseDialog, SIGNAL(saleSuccess()), this, SLOT(emitSaleSuccessToMainWindow()));

        // Mostrar el diálogo de respuesta del servidor
        responseDialog->exec();

        // Eliminar la instancia del diálogo después de que se haya cerrado
        delete responseDialog;
        qDebug() << "Return key pressed ";
        break;
    }
    case Qt::Key_F2:
        // Poner el foco en nameLine
        if (focusWidget() == nameLine)
            addressText->setFocus();
    case Qt::Key_F1:
        // Mover el cursor a la izquierda
        if (cursorPosition > 0)
        {
            currentLineEdit->setCursorPosition(cursorPosition - 1);
        }
        break;
    case Qt::Key_F4:
        // Mover el cursor a la derecha
        if (cursorPosition < text.size())
        {
            currentLineEdit->setCursorPosition(cursorPosition + 1);
        }
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void RecargaBilleteraScreen::emitSaleSuccessToMainWindow()
{
    qDebug() << "Widget Confirmación recarga billetera";
    emit showSaleScreen();
}

void RecargaBilleteraScreen::emitSaleErrorToMainWindow()
{
}
