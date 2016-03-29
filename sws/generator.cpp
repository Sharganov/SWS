#include "generator.h"
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <math.h>
#include <QFile>


QByteArray generateSineWave(int ip, int frequency, int sampleRate, int sampleSize)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);


    const int maxValue = pow(2,sampleSize - 1) - 1;
    const int valuesPerSecond = sampleRate*sampleSize/8;
    const float w = frequency*M_PI/sampleRate;
    const float b1 = 2.0 *cos(w);
    float y1 = sin(ip - w);
    float y2 = sin(ip- 2*w);

    for (int i = 0; i < valuesPerSecond; i++) {
        float y0 = b1*y1 - y2;
        y2 = y1;
        y1 = y0;
        out << (static_cast<short> (y0*maxValue));
    }
    buffer.close();

    return buffer.data();
}


/*
QByteArray generateSineWave2(int ip, int frequency, int sampleRate)
{
   QByteArray data;
   float w = frequency*M_PI/sampleRate;
   float b1 = 2.0 *cos(w);
   float y1 = sin(ip - w);
   float y2 = sin(ip- 2*w);

   for (int i = 0; i < sampleRate; i++) {
       float y0 = b1*y1 - y2;
       y2 = y1;
       y1 = y0;
       data.append(static_cast<char> (y0*127));
   }

   return data;
}
*/
