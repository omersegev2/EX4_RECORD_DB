#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "track_db.h"
#include "tracks_db.h"

struct tracks_db {
    LinkedList list;
    int num_of_tracks;
};


/* implement copy, match, compare print and destroy 
 * functions in order use the list
 *
*/

static ListElement copyTrack(ListElement element){

    if(element == NULL) return NULL;

    Track track = (Track)element;

    Track new_track = trackCopyTrack(track);

    return new_track;
}

static void freeTrack(ListElement element){
    
    Track track = (Track)element;
 
    trackFreeTrack(track);
}

static void printTrack(FILE* out, ListElement element){

    if(element == NULL) return;

    Track track = (Track)element;

    trackPrintTrack(out, track);
}

// This will be used to finde track by name
static int matchTrackByName(ListElement element, KeyForListElement key){

    if (element == NULL || key == NULL) return 0;

    Track track = (Track)element;
    char *name = (char *)key;

    // return 1 if is equals
    return trackMatchTrackByName(track, name);
}

// This will be used to copy list with filter function
int copyFuncForFilter(ListElement element, KeyForListElement key){
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
/* API functions implementation */

TracksDB tracksDbCreate(){

    TracksDB new_tracks_db = (TracksDB)malloc(sizeof(struct tracks_db));
    if(new_tracks_db == NULL) return NULL;

    new_tracks_db->num_of_tracks = 0;
    
    if(linkedListCreate(&(new_tracks_db->list),copyTrack,freeTrack,printTrack) != LIST_SUCCESS){
        free(new_tracks_db);
        return NULL;
    }

    return new_tracks_db;
}

void tracksDbDestroy(TracksDB tracks_db){

    if(tracks_db == NULL) return;
    
    linkedListDestroy(tracks_db->list);
    
    free(tracks_db);
}

TracksResult tracksDbAddTrack(TracksDB tracks_db, char *track_name, int track_length){

    if(tracks_db == NULL || track_name == NULL){
        return TRK_NULL_ARGUMENT;
    }

    if(track_length <= 0) return TRK_INVALID_TRACK_LENGTH;
    
    Track track = trackDbCreate(track_name, track_length);

    if(linkedListFind(tracks_db->list,track_name,matchTrackByName) == LIST_SUCCESS){
        trackDbDestroy(track);
        return TRK_TRACK_ALREADY_EXISTS;
    }

    if(linkedListInsertLast(tracks_db->list, track) != LIST_SUCCESS){
        trackDbDestroy(track);
        return TRK_OUT_OF_MEMORY;
    }

    trackDbDestroy(track);
    
    tracks_db->num_of_tracks++;

    return TRK_SUCCESS;
}

TracksResult tracksDbRemoveTrack(TracksDB tracks_db, char *track_name){
    
    if(tracks_db == NULL){
        return TRK_NULL_ARGUMENT;
    }
    linkedListGoToHead(tracks_db->list);
   
    if(linkedListFind(tracks_db->list, track_name, matchTrackByName) == LIST_SUCCESS){
        if(linkedListRemoveCurrent(tracks_db->list) != LIST_SUCCESS){
            return TRK_NULL_ARGUMENT;
        }
    } else {
        return TRK_TRACK_DOESNT_EXIST;
    }

    tracks_db->num_of_tracks--;

    return TRK_SUCCESS;
}

TracksResult tracksDbReportTracks(TracksDB tracks_db, FILE *out){

    if(tracks_db == NULL) return TRK_NULL_ARGUMENT;

    if(tracks_db->num_of_tracks == 0) return TRK_NO_TRACKS;
   
    if(linkedListPrint(tracks_db->list ,out ,tracks_db->num_of_tracks) != LIST_SUCCESS){
        return TRK_NULL_ARGUMENT;
    }

    return TRK_SUCCESS;
}

int findTrackInRecord(TracksDB tracks_db, char *track_name){
    
    if(tracks_db == NULL) return TRK_NULL_ARGUMENT;

    if(tracks_db->num_of_tracks == 0) return TRK_NO_TRACKS;

    linkedListGoToHead(tracks_db->list);

    if(linkedListFind(tracks_db->list,track_name,matchTrackByName) != LIST_SUCCESS){
        return 0;
    }

    return 1;
}

TracksDB tracksDbTracksCopy(TracksDB tracks_db){

    if(tracks_db == NULL || tracks_db->list == NULL) return NULL;
    
    TracksDB new_tracks = (TracksDB)malloc(sizeof(struct tracks_db));
    if(new_tracks == NULL){
        return NULL;
    }

    if(linkedListFilterElements(tracks_db->list, &(new_tracks->list),copyFuncForFilter, 0) != LIST_SUCCESS){
        free(new_tracks);
        return NULL;
    }

    new_tracks->num_of_tracks = tracks_db->num_of_tracks;

    return new_tracks;
}

