#ifndef __RECORD_DB_H__
#define __RECORD_DB_H__

#include "pr2ex4.h"

typedef struct record_db *Record;

int recordCompareRecordsByName(Record record1, Record record2);

Record recordCopyRecord(Record record);

void recordFreeRecord(Record record);

void recordPrintRecord(FILE* out, Record record);

int recordMatchRecordByName(Record record, char *name);

int recordMatchRecordByCategory(Record record, RecordsCategory category);

int recordMatchRecordByTrackName(Record record, char* trackName);

Record recordDbCreate(const char *name, int year, RecordsCategory category);

void recordDbDestroy(Record record);

RecordsResult recordDbAddTrackToRecord(Record record, char *trackName, int trackLength);

RecordsResult recordDbRemoveTrackFromRecord(Record record, char *trackName);

int getNumOfTracks(Record record);

#endif //__RECORD_DB_H__
