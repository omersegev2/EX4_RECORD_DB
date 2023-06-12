/* @author: Omer Segev
 * @id: 313772295
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "record_db.h"
#include "records_db.h"
#include "tracks_db.h"

#define MIN_YEAR 1900

struct RecordsDB_s {
    Set set;
    int num_of_records;
};

/* Implement copy, match, compare print and destroy
 * 
 */

static int compareRecordsByName(SetElement element1, SetElement element2){
    
    if(element1 == NULL || element2 == NULL){
        return 0;
    }

    Record record1 = (Record)element1;
    Record record2 = (Record)element2;

    return recordCompareRecordsByName(record1, record2);
}

static SetElement copyRecord(SetElement element){
    
    if(element == NULL) return NULL;

    Record record = (Record)element;

    Record new_record = recordCopyRecord(record);
    
    return new_record;
}

static void freeRecord(SetElement element){
   
   if(element){

        Record record = (Record)element;

        recordFreeRecord(record);
    }
}

static void printRecord(FILE* out, SetElement element){
    
    if(element == NULL) return;

    Record record = (Record)element;

    recordPrintRecord(out, record);
}

// This will be used to find record by name
static int matchRecordByName(SetElement element, KeyForSetElement key){

    if(element == NULL || key == NULL){
        return 0;
    }

    Record record = (Record)element;
    char *name = (char *)key;

    return recordMatchRecordByName(record, name);
}

// This will be used to filter record by category
static int matchRecordByCategory(SetElement element, KeyForSetElement key){
    
    if(element == NULL) return 0;
    
    Record record = (Record)element;
    RecordsCategory category = (RecordsCategory)key;

    return recordMatchRecordByCategory(record, category);
}

// This will be used to filter record with containing track
static int matchRecordByTrackName(SetElement element, KeyForSetElement key){
    
    if(element == NULL) return 0;
    
    Record record = (Record)element;
    char *track_name = (char *)key;

    //if findTrackInRecord return 1 its add record to set
    return recordMatchRecordByTrackName(record, track_name);
}

///////////////////////////////////////////////////////////////////////////////
/* API functions implementation */

RecordsDB recordsDbCreate(){

    RecordsDB new_records_db = (RecordsDB)malloc(sizeof(struct RecordsDB_s));
    if(new_records_db == NULL) return NULL;

    new_records_db->num_of_records = 0;

    if(setCreate(&(new_records_db->set), compareRecordsByName, copyRecord, freeRecord, printRecord) != SET_SUCCESS){
        free(new_records_db);
        return NULL;
    }

    return new_records_db;
}

void recordsDbDestroy(RecordsDB records_db){

    if(records_db == NULL) return;

    if(records_db->set == NULL) {
        free(records_db);
        return;
    }

    setDestroy(records_db->set);
    free(records_db);
}
    
RecordsResult recordsDbAddRecord(RecordsDB rdb, const char *name, int year, RecordsCategory category){

    if(rdb == NULL || name == NULL) return RDB_NULL_ARGUMENT;

    if(year < MIN_YEAR){
        return RDB_INVALID_YEAR;
    }
    
    if(category > CLASSIC || category < ROCK){
        return RDB_INVALID_CATEGORY;
    }
    
    Record record = recordDbCreate(name, year, category);

    SetResult res = setAdd(rdb->set, record);

    if(res != SET_SUCCESS){

        recordDbDestroy(record);

        if(res == SET_OUT_OF_MEMORY){
            return RDB_OUT_OF_MEMORY;
        }

        if(res == SET_ELEMENT_EXISTS){
            return RDB_RECORD_ALREADY_EXISTS;
        }

        return RDB_NULL_ARGUMENT;
    }

    recordDbDestroy(record);

    rdb->num_of_records++;

    return RDB_SUCCESS;
}

RecordsResult recordsDbRemoveRecord(RecordsDB rdb, char *name){

    if(rdb == NULL || name == NULL){
        return RDB_NULL_ARGUMENT;
    }
   
    Record record;

    SetResult res = setFind(rdb->set, (SetElement *)&record, name, matchRecordByName);

    if(res != SET_SUCCESS){
        if(res == SET_ELEMENT_DOES_NOT_EXIST)
            return RDB_RECORD_DOESNT_EXIST;
        return RDB_NULL_ARGUMENT;
    }

    res = setRemove(rdb->set, (SetElement *)record);

    if(res != SET_SUCCESS){
        if(res == SET_ELEMENT_DOES_NOT_EXIST)
            return RDB_RECORD_DOESNT_EXIST;
        return RDB_NULL_ARGUMENT;
    }

    rdb->num_of_records--;

    return RDB_SUCCESS;
}

RecordsResult recordsDbAddTrackToRecord (RecordsDB rdb, char *recordName, char *trackName, int trackLength){

    Record record; 

    SetResult res = setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName);

    if(res != SET_SUCCESS){
        if(res == SET_ELEMENT_DOES_NOT_EXIST)
            return RDB_RECORD_DOESNT_EXIST;
        return RDB_NULL_ARGUMENT;
    }

    return recordDbAddTrackToRecord(record,trackName,trackLength);
}

RecordsResult recordsDbRemoveTrackFromRecord (RecordsDB rdb, char *recordName, char *trackName){

    if(rdb == NULL || recordName == NULL || trackName == NULL){
        return RDB_NULL_ARGUMENT;
    }

    Record record; 

    SetResult res = setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName);

    if(res != SET_SUCCESS){
        if(res == SET_ELEMENT_DOES_NOT_EXIST)
            return RDB_RECORD_DOESNT_EXIST;
        return RDB_NULL_ARGUMENT;
    }

    return recordDbRemoveTrackFromRecord(record,trackName);
}

RecordsResult recordsDbReportRecords (RecordsDB rdb, RecordsCategory category){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Set set;

    SetResult res = setFilter(rdb->set, &set, (SetElement *)category, matchRecordByCategory);

    if(res != SET_SUCCESS){
        if(res == SET_OUT_OF_MEMORY)
            return RDB_OUT_OF_MEMORY;
        return RDB_NULL_ARGUMENT;
    }
    
    if(setGetSize(set) <= 0){
        setDestroy(set);
        return RDB_NO_RECORDS;
    }
    
    if(setPrintSorted(set,stdout,rdb->num_of_records, compareRecordsByName) != SET_SUCCESS){
        setDestroy(set);
        return RDB_NULL_ARGUMENT;
    }

    setDestroy(set);

    return RDB_SUCCESS;
}

RecordsResult recordsDbReportTracksOfRecord(RecordsDB rdb, char *recordName){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Record record; 

    SetResult res = setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName);

    if(res != SET_SUCCESS){
        if(res == SET_ELEMENT_DOES_NOT_EXIST)
            return RDB_RECORD_DOESNT_EXIST;
        return RDB_NULL_ARGUMENT;
    }

    if(getNumOfTracks(record) == 0) return RDB_NO_TRACKS;

    printRecord(stdout,record);

    return RDB_SUCCESS;
}

RecordsResult recordsDbReportContainingRecords(RecordsDB rdb, char *trackName){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Set set;

    SetResult res = setFilter(rdb->set, &set, trackName, matchRecordByTrackName);

    if(res != SET_SUCCESS){
        if(res == SET_OUT_OF_MEMORY)
            return RDB_OUT_OF_MEMORY;
        return RDB_NULL_ARGUMENT;
    }

    int size = setGetSize(set);

    if(size <= 0){
        setDestroy(set);
        return RDB_TRACK_DOESNT_EXIST;
    }

    if(setPrintSorted(set,stdout, size, compareRecordsByName) != SET_SUCCESS){
        setDestroy(set);
        return RDB_NULL_ARGUMENT;
    }

    setDestroy(set);
  
    return RDB_SUCCESS;
}

