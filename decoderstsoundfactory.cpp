#include "decoderstsoundfactory.h"
#include "decoder_stsound.h"
#include "stsoundhelper.h"

#include <QMessageBox>

bool DecoderStSoundFactory::canDecode(QIODevice *input) const
{
    const QFile * const file = qobject_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    StSoundHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderStSoundFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("StSound Plugin");
    properties.shortName = "stsound";
    properties.filters << "*.ym";
    properties.description = "ST-Sound, ATARI-ST Audio File";
    properties.protocols << "file";
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderStSoundFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderStSound(path);
}

QList<TrackInfo*> DecoderStSoundFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    StSoundHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::MetaData)
    {
        info->setValue(Qmmp::TITLE, helper.title());
        info->setValue(Qmmp::ARTIST, helper.author());
        info->setValue(Qmmp::COMMENT, helper.comment());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "StSound YM");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderStSoundFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderStSoundFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderStSoundFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About YM Reader Plugin"),
                       tr("Qmmp YM Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderStSoundFactory::translation() const
{
    return QString();
}
