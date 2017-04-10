#ifndef FILESTREAM_H
#define FILESTREAM_H
#include "QDataStream"


class FileStream
{
public:
    FileStream();
    qint64 ReadInt64(QDataStream& file);
    qint32 ReadInt32(QDataStream& file);
    qint16 ReadInt16(QDataStream& file);
    qint8 ReadInt8(QDataStream& file);
    quint64 ReadUInt64(QDataStream& file);
    quint32 ReadUInt32(QDataStream& file);
    quint16 ReadUInt16(QDataStream& file);
    quint8 ReadUInt8(QDataStream& file);
    char* ReadBytes(QDataStream& file, int len);
    void WriteInt64(QDataStream& file, qint64 val);
    void WriteInt32(QDataStream& file, qint32 val);
    void WriteInt16(QDataStream& file, qint16 val);
    void WriteInt8(QDataStream& file, qint8 val);
    void WriteUInt64(QDataStream& file, quint64 val);
    void WriteUInt32(QDataStream& file, quint32 val);
    void WriteUInt16(QDataStream& file, quint16 val);
    void WriteUInt8(QDataStream& file, quint8 val);
    void WriteBytes(QDataStream& file, char* val, int len);
    void seek(QDataStream& file, qint64 pos);
   };

#endif // FILESTREAM_H
