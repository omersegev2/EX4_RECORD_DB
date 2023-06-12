#ifndef __TRACK_DB_H__
#define __TRACK_DB_H__

#include "pr2ex4.h"

typedef struct track_db *Track;

Track trackCopyTrack(Track track);

void trackFreeTrack(Track track);

void trackPrintTrack(FILE* out, Track track);

int trackMatchTrackByName(Track track, char* name);

Track trackDbCreate(char *track_name, int track_length);

void trackDbDestroy(Track track);

#endif //__TRACK_DB_H__

