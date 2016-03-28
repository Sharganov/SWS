#include "generator.h"
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <math.h>
#include <QFile>

QByteArray newOneALgorithm(int frequency, int sampleRate)// MCF algorithm
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);

    int w = frequency*M_PI/sampleRate;
    float f = (180 - w)/2;
    float x0 = 0;
    float y0 = -sin(f);
    float e = 2*cos(f);
    for (int i = 0; i<sampleRate; i++)
    {

        x0 = x0 - e*y0;
        out << (static_cast<int> (x0*127));
        y0 = e*x0 + y0;
    }
    return buffer.data();
}



QByteArray generateSineWave2(int ip, int frequency, int sampleRate)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);

    float w = frequency*M_PI/sampleRate;
    float b1 = 2.0 *cos(w);
    float y1 = sin(ip - w);
    float y2 = sin(ip- 2*w);

    for (int i = 0; i < sampleRate; i++) {
        float y0 = b1*y1 - y2;
        y2 = y1;
        y1 = y0;
        out << (static_cast<short> (y0*32767));
    }
    buffer.close();

    return buffer.data();
}



QByteArray generateSineWave(int ip, int frequency, int sampleRate)
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

