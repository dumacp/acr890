#include <QtGui>
#include "homescreen.h"
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
// #include <QList>
#include <QNetworkRequest>
// #include <QSslError>
#include <QStringList>
#include <QTimer>
#include <QUrl>

#include <stdio.h>

QT_BEGIN_NAMESPACE
// class QSslError;
QT_END_NAMESPACE

QT_USE_NAMESPACE

/* HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
{
    // Crear un layout vertical para colocar los elementos de la pantalla de inicio
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Agregar un QLabel para el texto centrado

    QLabel *titleLabel = new QLabel("Nebula E");
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Agregar un QLabel para el subtítulo
    QLabel *subtitleLabel = new QLabel("POS");
    subtitleLabel->setFont(QFont("Arial", 12, QFont::Bold));
    layout->addWidget(subtitleLabel);

    // Agregar un QTextEdit para la descripción
    QTextEdit *descriptionTextEdit = new QTextEdit("ZS544587");
    descriptionTextEdit->setReadOnly(true);              // Deshabilitar la edición
    descriptionTextEdit->setStyleSheet("border: none;"); // Eliminar cualquier estilo
    layout->addWidget(descriptionTextEdit);

    // Ajustar el espaciado entre los elementos
    layout->setSpacing(2);

    // Información del POS - subtitle
    QLabel *posData = new QLabel("Cajero");
    posData->setFont(QFont("Arial", 12, QFont::Bold));
    layout->addWidget(posData);

    // Información del POS - description
    QTextEdit *descriptionPosData = new QTextEdit("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
    descriptionPosData->setReadOnly(true);              // Deshabilitar la edición
    descriptionPosData->setStyleSheet("border: none;"); // Eliminar cualquier estilo
    layout->addWidget(descriptionPosData);

    // Establecer el layout para la ventana
    setLayout(layout);
}
 */

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
{
    // Crear un layout vertical para colocar los elementos de la pantalla de inicio
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Agregar un QLabel para el texto centrado
    QLabel *titleLabel = new QLabel("NebulaE");
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Agregar un espacio flexible para separar los elementos
    layout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Agregar un QLabel para el subtítulo del POS
    QLabel *subtitleLabel = new QLabel("POS");
    subtitleLabel->setFont(QFont("Arial", 12, QFont::Bold));
    subtitleLabel->setStyleSheet("border: none;"); // Eliminar cualquier estilo
    layout->addWidget(subtitleLabel);

    // Agregar un QTextEdit para la información del POS
    QTextEdit *descriptionTextEdit = new QTextEdit("ZS544587");
    descriptionTextEdit->setReadOnly(true);    // Deshabilitar la edición
    descriptionTextEdit->setMaximumHeight(50); // Establecer la altura máxima
    descriptionTextEdit->setMinimumHeight(30);
    descriptionTextEdit->setStyleSheet("border: none;"); // Eliminar cualquier estilo
    layout->addWidget(descriptionTextEdit);

    // Agregar un QLabel para la información del POS - subtítulo
    QLabel *posData = new QLabel("Cajero");
    posData->setFont(QFont("Arial", 12, QFont::Bold));
    layout->addWidget(posData);

    // Agregar un QTextEdit para la información del POS - descripción
    QTextEdit *descriptionPosData = new QTextEdit("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
    descriptionPosData->setReadOnly(true);              // Deshabilitar la edición
    descriptionPosData->setStyleSheet("border: none;"); // Reducir el margen superior
    layout->addWidget(descriptionPosData);

    // Establecer el layout para la ventana
    setLayout(layout);
}
