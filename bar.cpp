#include "bar.h"
/* This library is used to dealing with Binary ARchive format
 * present in KH2 games.
 * Current limitations: can only deal with one file at a time
 * This is a design choice and could be prevented if need
 * happens*/
/* File format:
 * char[4] -> BAR\x01
 * UInt32 -> File count
 * Int32 -> Reserved (BARptr)
 * Int32 -> Reserved
 * foreach entries:
 * 	UInt16 -> type
 * 	UInt16 -> duplicate
 * 	char[4] -> ID
 *  UInt32 -> Entry data absolute offset
 *  UInt32 -> Entry data length
 * void -> Entry absolute datas
 * */
/* IDs can be seen as names and types
 * as file format extension
 * Here is a list of known types:
 *
 * 	Unk1 = 0x00,
    BAR = 0x01,
    Binary file = 0x02,
    AI file = 0x03,
    MDLX = 0x04,
    DOCT = 0x05,
    Hitbox = 0x06,
    RawTexture = 0x07,
    TIM2 = 0x0A,
    COCT_2 = 0x0B,
    SPWN = 0x0C,
    SKY = 0x0E,
    COCT_3 = 0x0F,
    BAR_2 = 0x11,
    PAX = 0x12,
    COCT_4 = 0x13,
    BAR_3 = 0x14,
    ANL = 0x16,
    Hurtbox = 0x17,
    IMGD = 0x18,
    SEQD = 0x19,
    LAYERD = 0x1C,
    IMGZ = 0x1D,
    BAR_4 = 0x1E,
    SEB = 0x1F,
    WD = 0x20,
    VSB = 0x22,
    TBMP = 0x24,
    BAR_5 = 0x2E,
    VIBD = 0x2F,
    VAG = 0x30 */
BAR::BAR()
{
    std::vector<BARFile> fileList;
}
void BAR::load(QFile *file)
{
    QDataStream Sfile(file);
    MainWindow window;
    FileStream stream;
    qint32 magic = stream.ReadInt32(Sfile);

    if(file->size() < 16 || magic != 0x42415201){
        window.ErrorMessage((QString)"Not a valid BAR file!");
        return;
    }
    quint32 fileC = stream.ReadUInt32(Sfile);
    qDebug() << "Loading a BAR file with" << fileC << "entries";
    stream.seek(Sfile, 16);
    for(int i =0; i < (int)fileC; i++)
    {
        BARFile bf;
        bf.type = stream.ReadUInt16(Sfile);
        bf.dup = stream.ReadUInt16(Sfile);
        bf.id = stream.ReadBytes(Sfile, 4);
        qint64 lpos=file->pos()+8;

        quint32 pos = stream.ReadUInt32(Sfile);
        quint32 len = stream.ReadUInt32(Sfile);
        qDebug() << "Entry 1 type:" << bf.type << "pos:" << pos << "len:" << len;
        stream.seek(Sfile, pos);
        char* dataptr = stream.ReadBytes(Sfile, len);
        bf.data.insert(bf.data.begin(), dataptr, dataptr+len);
        free(dataptr);
        fileList.push_back(bf);
        stream.seek(Sfile, lpos);
    }
}

int BAR::fileCount()
{
    return (int)fileList.size();
}
void BAR::save(QFile *file)
{
    QDataStream Sfile(file);
    FileStream stream;
    stream.seek(Sfile, 0);
    stream.WriteInt32(Sfile, 0x42415201);
    stream.WriteUInt32(Sfile, (quint32)fileCount());
    stream.WriteUInt64(Sfile, (quint64)0);
    qint64 offset = 16* ((quint32)fileCount() +1);
    for(int i=0; i < fileCount(); i++)
    {
       stream.seek(Sfile,(quint64)16*(i+1));
       BARFile bf = fileList[i];
       stream.WriteUInt16(Sfile, bf.type);
       //TODO: Check if this is a duplicate instead of writing cached data
       stream.WriteUInt16(Sfile, bf.dup);
       stream.WriteBytes(Sfile, bf.id, 4);
       stream.WriteUInt32(Sfile, (quint32)offset);
       stream.WriteUInt32(Sfile, (quint32)bf.data.size());
       quint32 szPad = (quint32)ceil((double)bf.data.size() / 16) * 16;
       stream.seek(Sfile, offset);
       stream.WriteBytes(Sfile, &bf.data[0], (quint32)bf.data.size());
       offset+=(qint64)szPad;
    }
}
