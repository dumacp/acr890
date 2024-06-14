#include "dialog.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

ResponseDialog::ResponseDialog(QWidget *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    // Establecer el tamaño fijo del diálogo
    setFixedSize(220, 250); // Ancho total de 50px

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes
    layout->setSpacing(5);                  // Ajustar el espacio entre los elementos a 10 píxeles

    // Icono central
    iconLabel = new QLabel(this); // Declarar iconLabel como miembro de la clase
    iconLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(iconLabel, 0, Qt::AlignCenter); // Añade el icono al layout

    // Etiqueta para mostrar la respuesta
    responseLabel = new QLabel(this);
    responseLabel->setWordWrap(true);                            // Habilita el ajuste de texto automático
    responseLabel->setAlignment(Qt::AlignCenter);                // Centra el texto horizontalmente
    responseLabel->setStyleSheet("QLabel { font-size: 14px; }"); // Establece el tamaño de la fuente
    layout->addWidget(responseLabel, 0, Qt::AlignCenter);        // Añade la etiqueta al layout

    // Texto adicional entre el título y los botones
    additionalTextLabel = new QLabel(this);
    additionalTextLabel->setAlignment(Qt::AlignCenter);
    additionalTextLabel->setVisible(false);                     // Por defecto no visible
    layout->addWidget(additionalTextLabel, 0, Qt::AlignCenter); // Añade el texto adicional al layout

    // Crear un layout horizontal para los botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Botón de cierre - continuar
    closeButton = new QPushButton("", this);
    buttonLayout->addWidget(closeButton, 0, Qt::AlignCenter); // Añade el botón al layout horizontal

    // Botón de cancelar - continuar
    cancelButton = new QPushButton("", this);
    cancelButton->setVisible(false);                           // Por defecto no visible
    buttonLayout->addWidget(cancelButton, 0, Qt::AlignCenter); // Añade el botón al layout horizontal

    // Agregar el layout horizontal al layout vertical
    layout->addLayout(buttonLayout); // Agrega el layout horizontal al layout vertical sin especificar la alineación

    // Conectar el botón de cierre a la ranura de cierre del diálogo

    // Login Success
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitLoginSuccessAndClose()));

    // Login Error
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitLoginErrorAndClose()));

    // Sale Success
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitSaleSuccessAndClose()));

    // Sale Error
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitSaleErrorAndClose()));

    // Sale Cancel
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    // Establecer la hoja de estilo del diálogo
    setStyleSheet("QDialog { background-color: white; border: 1px solid black; border-radius: 2px;}"                      // Fondo blanco
                  "QLabel { font-size: 14px; }"                                                                           // Estilo de la etiqueta de respuesta
                  "QPushButton { font-size: 14px; padding: 5px 10px; border: 1px solid black; background-color: white; }" // Estilo del botón
                  "QPushButton:hover { background-color: #C0C0C0; }");                                                    // Estilo del botón cuando el cursor está encima

    // Ocultar la barra de título del diálogo
    setWindowFlags(Qt::FramelessWindowHint);

    // Centrar el diálogo en la pantalla
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - width()) / 2;
    int y = (screenHeight - height()) / 2;
    move(x, y);
}

void ResponseDialog::setResponseText(const QString &responseText, const QString &bold)
{
    responseLabel->setText(responseText);
    if (bold == "yes")
    {
        responseLabel->setFont(QFont("Arial", 12, QFont::Bold));
        additionalTextLabel->setVisible(true);
    }
}

void ResponseDialog::setAdditionalText(const QString &responseText)
{
    additionalTextLabel->setText(responseText);
    additionalTextLabel->setVisible(true);
}

void ResponseDialog::setResponseIcon(const QIcon &icon)
{
    iconLabel->setPixmap(icon.pixmap(64, 64)); // Establece el tamaño del icono
}

void ResponseDialog::setCloseButtonText(const QString &text)
{
    closeButton->setText(text);
}

void ResponseDialog::setCancelButtonText(const QString &text)
{
    cancelButton->setText(text);
    cancelButton->setVisible(true);
}

void ResponseDialog::emitLoginSuccessAndClose()
{

    emit loginSuccess();
    close();
}

void ResponseDialog::emitLoginErrorAndClose()
{
    emit loginError();
    close();
}

void ResponseDialog::emitSaleSuccessAndClose()
{
    emit saleSuccess();
    close();
}

void ResponseDialog::emitSaleErrorAndClose()
{
    emit saleError();
    close();
}

void ResponseDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        // Si se presiona la tecla Esc, cierra el diálogo
        close();
    }
    else
    {
        // Si no, deja que el diálogo maneje el evento normalmente
        QDialog::keyPressEvent(event);
    }
}