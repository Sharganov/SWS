#include "player.h"
#include "generator.h"
#include <QAudioOutput>
#include <QBuffer>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

void playTone(float freqHz, int durationMs)
{
    const int sampleRate = 8000;
    const int sampleSize = 16;
    const int timeInterval = 70; //time to seek buffer in ms

    QTimer timer;
    timer.setSingleShot(true);
    timer.setInterval(durationMs);

    QByteArray audio_data = generateSineWave(0, freqHz, sampleRate, sampleSize);
    QBuffer audio_buffer(&audio_data);
    audio_buffer.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setSampleSize(sampleSize);
    format.setSampleRate(sampleRate);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::BigEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning()<<"Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    QAudioOutput output(info, format);
    output.setNotifyInterval(timeInterval);
    output.start(&audio_buffer);

    QEventLoop loop;

    QObject::connect(&output, SIGNAL(notify()), &loop, SLOT(quit()));
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timer.start();

    while(timer.isActive()) {
        audio_buffer.seek(0);
        loop.exec();

    }

    output.stop();

};
