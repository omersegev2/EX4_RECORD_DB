
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track_db.h"

struct track_db{
    char* track_name;
    unsigned int track_length;
};

/* implement copy, match, compare print and destroy 
 * functions in order use the list
 *
*/

Track trackCopyTrack(Track track){

    if(track == NULL) return NULL;

    Track new_track = (Track)malloc(sizeof(struct track_db));
    if(new_track == NULL) return NULL;

    new_track->track_length = track->track_length;
    
    new_track->track_name = (char *)malloc(strlen(track->track_name) + 1);
    if(track->track_name == NULL){
        free(new_track);
        return NULL;
    }

    strcpy(new_track->track_name,track->track_name);

    return new_track;
}

void trackFreeTrack(Track track){
    
    free(track->track_name);
    free(track); 
}

void trackPrintTrack(FILE* out, Track track){

    if(track == NULL) return;

    prog2_report_track(out, track->track_name, track->track_length);
}

// This will be used to finde track by name
int trackMatchTrackByName(Track track, char* name){

    if (track == NULL || name == NULL) return 0;

    // return 1 if is equals
    return strcmp(track->track_name,name)? 0: 1;
}

///////////////////////////////////////////////////////////////////////////////


Track trackDbCreate(char *track_name, int track_length){

    Track new_track = (Track)malloc(sizeof(struct track_db));
    if(new_track == NULL) return NULL;

    new_track->track_name = (char *)malloc(strlen(track_name) + 1);
    if(new_track->track_name == NULL){
        free(new_track);
        return NULL;
    }

    strcpy(new_track->track_name,track_name);
    new_track->track_length = track_length;

    return new_track;
}

void trackDbDestroy(Track track){
    free(track->track_name);
    free(track); 
}