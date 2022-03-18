#include "decoderstsoundfactory.h"
#include "decoder_stsound.h"
#include "stsoundhelper.h"

#include <QMessageBox>

bool DecoderStSoundFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderStSoundFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("StSound Plugin");
    properties.shortName = "stsound";
    properties.filters << "*.ym";
    properties.description = "ST-Sound, ATARI-ST Audio File";
    properties.noInput = true;
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
        const QMap<Qmmp::MetaData, QString> metaData(helper.readMetaData());
        for(auto itr = metaData.begin(); itr != metaData.end(); ++itr)
        {
            info->setValue(itr.key(), itr.value());
        }
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "StSound");
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
    QMessageBox::about (parent, tr("About YM Reader Plugin"),
                        tr("Qmmp YM Reader Plugin")+"\n"+
                        tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderStSoundFactory::translation() const
{
    return QString();
}
