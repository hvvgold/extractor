#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <unistd.h>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // qt

    QString ExtrTextFile = "extr";  // input text filename
    QString ExtrTextFileSuffix  = ".txt";
    QString cmd;                        // cmd string for system() call
    QString inputFile = argv[1];
    QFileInfo fi(inputFile);
    if(fi.suffix() == "pdf"){
        cmd = "pdftotext";

        cmd = cmd + QString(" ") + inputFile + QString(" ")+  ExtrTextFile +ExtrTextFileSuffix ;

    }else if(fi.suffix() == "jpg"){

        cmd = "tesseract";
        cmd = cmd + QString(" ") + inputFile + QString(" ") + ExtrTextFile +
                QString(" -l rus -psm 6");
    }
    else{
        qDebug() << "File format error.";
    }

    system(cmd.toAscii());

    QFile inExtrFile( ExtrTextFile  + ExtrTextFileSuffix);
    if ( !inExtrFile.open(QIODevice::ReadOnly | QIODevice::Text)){

        qDebug() << "File " << ExtrTextFile << " open failed.";
        return (int)false;
    }
    QString s = inExtrFile.readAll();
    QString indexStr = "8888";          // control info

    s.replace(QString("\n"),QString(" "));

    QStringList sl = s.split(" ");

    foreach(QString s, sl){
        if(s.contains(indexStr)){
            qDebug() << s;              // print to stdout(err)
        }
    }

    return a.exec();    // qt

}
