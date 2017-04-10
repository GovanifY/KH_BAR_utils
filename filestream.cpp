#include "filestream.h"
/* Portable FileStream utilities for Qt
 * Somehow reading uint doesn't change endianness so I have
 * to do that myself, otherwise leading to the absurd result
 * of uint==int which is NOT cool */
/* WARNING: As endianess is dependant per computer I made a
 * choice of storing Ints as BE and UInt as LE.
 * While this may be a design limitation if we hit positive
 * limit of Int in the future I made this to have an easy way
 * to store values.
 * In need of future modifications we can always
 * :s/UInt/IntLE/g */
FileStream::FileStream()
{
}
qint64 FileStream::ReadInt64(QDataStream& file)
{
    qint64 tmp;
    file.setByteOrder(QDataStream::BigEndian);
    file >> tmp;
    return tmp;
}

qint32 FileStream::ReadInt32(QDataStream& file)
{
    qint32 tmp;
    file.setByteOrder(QDataStream::BigEndian);
    file >> tmp;
    return tmp;
}

qint16 FileStream::ReadInt16(QDataStream& file)
{
    qint16 tmp;
    file.setByteOrder(QDataStream::BigEndian);
    file >> tmp;
    return tmp;
}

qint8 FileStream::ReadInt8(QDataStream& file)
{
    qint8 tmp;
    file.setByteOrder(QDataStream::BigEndian);
    file >> tmp;
    return tmp;
}

quint64 FileStream::ReadUInt64(QDataStream& file)
{
    quint64 tmp;
    file.setByteOrder(QDataStream::LittleEndian);
    file >> tmp;
    return tmp;
}

quint32 FileStream::ReadUInt32(QDataStream& file)
{
    quint32 tmp;
    file.setByteOrder(QDataStream::LittleEndian);
    file >> tmp;
    return tmp;
}

quint16 FileStream::ReadUInt16(QDataStream& file)
{
    quint16 tmp;
    file.setByteOrder(QDataStream::LittleEndian);
    file >> tmp;
    return tmp;
}

quint8 FileStream::ReadUInt8(QDataStream& file)
{
    quint8 tmp;
    file.setByteOrder(QDataStream::LittleEndian);
    file >> tmp;
    return tmp;
}

char* FileStream::ReadBytes(QDataStream& file, int len)
{
    file.setByteOrder(QDataStream::BigEndian);
    char* tmp = new char[len];
    file.readRawData(tmp, len);
    return tmp;
}

void FileStream::WriteInt64(QDataStream& file, qint64 val)
{
    file.setByteOrder(QDataStream::BigEndian);
    file << val;
}

void FileStream::WriteInt32(QDataStream& file, qint32 val)
{
    file.setByteOrder(QDataStream::BigEndian);
    file << val;
}

void FileStream::WriteInt16(QDataStream& file, qint16 val)
{
    file.setByteOrder(QDataStream::BigEndian);
    file << val;
}

void FileStream::WriteInt8(QDataStream& file, qint8 val)
{
    file.setByteOrder(QDataStream::BigEndian);
    file << val;
}

void FileStream::WriteUInt64(QDataStream& file, quint64 val)
{
    file.setByteOrder(QDataStream::LittleEndian);
    file << val;
}

void FileStream::WriteUInt32(QDataStream& file, quint32 val)
{
    file.setByteOrder(QDataStream::LittleEndian);
    file << val;
}

void FileStream::WriteUInt16(QDataStream& file, quint16 val)
{
    file.setByteOrder(QDataStream::LittleEndian);
    file << val;
}

void FileStream::WriteUInt8(QDataStream& file, quint8 val)
{
    file.setByteOrder(QDataStream::LittleEndian);
    file << val;
}

void FileStream::WriteBytes(QDataStream& file, char* val, int len)
{
    file.setByteOrder(QDataStream::BigEndian);
    file.writeRawData(val, len);
}


void FileStream::seek(QDataStream& file, qint64 pos)
{
    file.device()->seek(pos);
}
