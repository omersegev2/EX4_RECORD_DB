#ifndef __TRACKS_DB_H__
#define __TRACKS_DB_H__

typedef struct tracks_db *TracksDB;

#include "pr2ex4.h"

typedef enum TracksResult_e {
    TRK_SUCCESS,
    TRK_NULL_ARGUMENT,
    TRK_RECORD_DOESNT_EXIST,
    TRK_INVALID_YEAR,
    TRK_INVALID_CATEGORY,
    TRK_RECORD_ALREADY_EXISTS,
    TRK_NO_RECORDS,
    TRK_INVALID_TRACK_LENGTH,
    TRK_TRACK_ALREADY_EXISTS,
    TRK_NO_TRACKS,
    TRK_TRACK_DOESNT_EXIST,
    TRK_OUT_OF_MEMORY
} TracksResult;

TracksDB tracksDbCreate();

void tracksDbDestroy(TracksDB tracks_db);

TracksResult tracksDbAddTrack(TracksDB tracks_db, char *track_name, int track_length);

TracksResult tracksDbRemoveTrack(TracksDB tracks_db, char *track_name);

TracksResult tracksDbReportTracks(TracksDB tracks_db, FILE *out);

TracksDB tracksDbTracksCopy(TracksDB tracks_db);

int findTrackInRecord(TracksDB tracks_db, char *track_name);

#endif // __TRACKS_DB_H__
