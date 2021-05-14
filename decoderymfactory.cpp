#include "decoderymfactory.h"
#include "decoder_ym.h"

#include <QFileInfo>
#include <QMessageBox>

bool DecoderYmFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderYmFactory::properties() const
{
    DecoderProperties properties;
    properties.name = "YM Plugin";
    properties.shortName = "ym";
    properties.filters << "*.ym";
    properties.description = "ST-Sound, ATARI-ST Audio File";
    properties.protocols << "file";
    properties.noInput = true;
    return properties;
}

Decoder *DecoderYmFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderYm(path);
}

QList<TrackInfo*> DecoderYmFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);

    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    CYmMusic *music = new CYmMusic;
    if(!music->load(qPrintable(path)))
    {
        delete info;
        return QList<TrackInfo*>();
    }

    ymMusicInfo_t musicInfo;
    music->getMusicInfo(&musicInfo);

    if(parts & TrackInfo::MetaData)
    {
        char* title = strdup(musicInfo.pSongName);
        char* composer = strdup(musicInfo.pSongAuthor);
        char* comment = strdup(musicInfo.pSongComment);

        info->setValue(Qmmp::TITLE, QString::fromUtf8(title).trimmed());
        info->setValue(Qmmp::COMPOSER, QString::fromUtf8(composer).trimmed());
        info->setValue(Qmmp::COMMENT, QString::fromUtf8(comment).trimmed());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, (QFileInfo(path).size() * 8.0) / musicInfo.musicTimeInMs + 1.0f);
        info->setValue(Qmmp::SAMPLERATE, 44100);
        info->setValue(Qmmp::CHANNELS, 2);
        info->setValue(Qmmp::FORMAT_NAME, "YM");
        info->setDuration(musicInfo.musicTimeInMs);
    }

    delete music;
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderYmFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderYmFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderYmFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About YM Reader Plugin"),
                        tr("Qmmp YM Reader Plugin")+"\n"+
                        tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderYmFactory::translation() const
{
    return QString();
}
