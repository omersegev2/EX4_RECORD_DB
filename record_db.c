#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracks_db.h"
#include "record_db.h"

#define MIN_YEAR 1900

struct record_db{
    char *name;
    unsigned int year;
    unsigned int num_of_tracks_added;
    TracksDB tracks;
    RecordsCategory category;
};

///////////////////////////////////////////////////////////////////////////////

RecordsResult track_result_to_record_result(TracksResult res){
    switch (res) {
        case TRK_SUCCESS:
            return RDB_SUCCESS;
        case TRK_NULL_ARGUMENT:
            return RDB_NULL_ARGUMENT;
        case TRK_RECORD_DOESNT_EXIST:
            return RDB_RECORD_DOESNT_EXIST;
        case TRK_INVALID_YEAR:
            return RDB_INVALID_YEAR;
        case TRK_INVALID_CATEGORY:
            return RDB_INVALID_CATEGORY;
        case TRK_RECORD_ALREADY_EXISTS:
            return RDB_RECORD_ALREADY_EXISTS;
        case TRK_NO_RECORDS:
            return RDB_NO_RECORDS;
        case TRK_INVALID_TRACK_LENGTH:
            return RDB_INVALID_TRACK_LENGTH;
        case TRK_TRACK_ALREADY_EXISTS:
            return RDB_TRACK_ALREADY_EXISTS;
        case TRK_NO_TRACKS:
            return RDB_NO_TRACKS;
        case TRK_TRACK_DOESNT_EXIST:
            return RDB_TRACK_DOESNT_EXIST;
        case TRK_OUT_OF_MEMORY:
            return RDB_OUT_OF_MEMORY;
        default:
            return RDB_NULL_ARGUMENT;
    }
}

int recordCompareRecordsByName(Record record1, Record record2){
    
    if(record1 == NULL || record2 == NULL){
        return 0;
    }

    return strcmp(record1->name,record2->name);
}

Record recordCopyRecord(Record record){
    
    if(record == NULL) return NULL;

    Record new_record = (Record)malloc(sizeof(struct record_db));
    if(new_record == NULL) return NULL;

    new_record->name = (char *)malloc(strlen(record->name)+1);
    if(new_record->name == NULL){
        free(new_record);
        return NULL;
    }

    strcpy(new_record->name,record->name);
    new_record->num_of_tracks_added = record->num_of_tracks_added;
    new_record->category = record->category;
    new_record->year = record->year;
    
    new_record->tracks = tracksDbTracksCopy(record->tracks);
    
    return new_record;
}

void recordFreeRecord(Record record){
   
   if(record){

        if(record->tracks != NULL){
            tracksDbDestroy(record->tracks);
        }

        free(record->name);
        free(record);
    }
}

void recordPrintRecord(FILE* out, Record record){
    
    if(record == NULL) return;

    prog2_report_record(out, record->name, record->year, record->num_of_tracks_added, record->category);

    tracksDbReportTracks(record->tracks, out);
}

// This will be used to find record by name
int recordMatchRecordByName(Record record, char *name){

    if(record == NULL || name == NULL){
        return 0;
    }

    return strcmp(record->name, name)? 0 : 1;
}

// This will be used to filter record by category
int recordMatchRecordByCategory(Record record, RecordsCategory category){
    
    if(record == NULL) return 0;
    
    if(category == ALL_CATEGORIES) return 1;

    return record->category == category;
}

// This will be used to filter record with containing track
int recordMatchRecordByTrackName(Record record, char* trackName){
    
    if(record == NULL) return 0;
    
    //if findTrackInRecord return 1 its add record to set
    return findTrackInRecord(record->tracks, trackName);

}

///////////////////////////////////////////////////////////////////////////////

Record recordDbCreate(const char *name, int year, RecordsCategory category){

    Record record = (Record)malloc(sizeof(struct record_db));
    if(record == NULL) return NULL;

    record->year = year;

    record->name = (char *)malloc(strlen(name)+1);
    if(record->name == NULL) {
        free(record);
        return NULL;
    }
    
    strcpy(record->name, name);
    
    record->category = category;
    record->num_of_tracks_added = 0;

    record->tracks = tracksDbCreate();
    
    return record;
}

void recordDbDestroy(Record record){
    recordFreeRecord(record);
}

RecordsResult recordDbAddTrackToRecord(Record record, char *trackName, int trackLength){

    TracksResult track_res = tracksDbAddTrack(record->tracks,trackName,trackLength);

    RecordsResult res = track_result_to_record_result(track_res);
    if(res == RDB_SUCCESS) 
        record->num_of_tracks_added++;

    return res;
}

RecordsResult recordDbRemoveTrackFromRecord(Record record, char *trackName){
    
    TracksResult track_res = tracksDbRemoveTrack(record->tracks,trackName);

    RecordsResult res = track_result_to_record_result(track_res);
    if(res == RDB_SUCCESS) 
        record->num_of_tracks_added--;

    return res;
}

int getNumOfTracks(Record record){
    int size = record->num_of_tracks_added;
    return size;
}
