#include "records_db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *records_result_strings[] = {
    "RDB_SUCCESS",
    "RDB_NULL_ARGUMENT",
    "RDB_RECORD_DOESNT_EXIST",
    "RDB_INVALID_YEAR",
    "RDB_INVALID_CATEGORY",
    "RDB_RECORD_ALREADY_EXISTS",
    "RDB_NO_RECORDS",
    "RDB_INVALID_TRACK_LENGTH",
    "RDB_TRACK_ALREADY_EXISTS",
    "RDB_NO_TRACKS",
    "RDB_TRACK_DOESNT_EXIST",
    "RDB_OUT_OF_MEMORY",
};

const char *records_result(RecordsResult result)
{
    if (result < 0 || result >= sizeof(records_result_strings) / sizeof(char *))
        return "Unknown";
    return records_result_strings[result];
}

RecordsDB rdb = NULL;

void records_app_print_error_message(FILE *err_ch, RecordsResult result)
{
    fprintf(err_ch, " ***** Error: %s *****\n", records_result(result));
}

void tester_handle_result(RecordsResult result)
{
    if (result != RDB_SUCCESS)
        records_app_print_error_message(stderr, result);
    if (result == RDB_OUT_OF_MEMORY)
    {
        recordsDbDestroy(rdb);
        exit(0);
    }
}

void print_msg(const char *msg)
{
    printf("%s\n", msg);
    for (int i = 0; i < strlen(msg); i++)
        printf("-");
    printf("\n");
}
void test1()
{
    print_msg("Test 111111");
    
    rdb = recordsDbCreate();
    if (rdb == NULL)
    {
        records_app_print_error_message(stderr, RDB_OUT_OF_MEMORY);
        exit(0);
    }

    print_msg("Add records");
    tester_handle_result(recordsDbAddRecord(rdb, "Nevermind", 1991, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Hotel California", 1976, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Led Zeppelin IV", 1971, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Wall", 1979, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Rumours", 1977, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Joshua Tree", 1987, HIP_HOP));
    tester_handle_result(recordsDbAddRecord(rdb, "The Chronic", 1992, HIP_HOP));
    tester_handle_result(recordsDbAddRecord(rdb, "Exile on Main St.", 1972, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Doors", 1967, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Miseducation of Lauryn Hill", 1998, HIP_HOP));
    tester_handle_result(recordsDbAddRecord(rdb, "Thriller", 1982, POP));
    tester_handle_result(recordsDbAddRecord(rdb, "Back in Black", 1980, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Dark Side of the Moon", 1973, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Greatest Hits (1971-1975)", 1976, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Saturday Night Fever", 1977, POP));
    tester_handle_result(recordsDbAddRecord(rdb, "Ropin' the Wind", 1991, COUNTRY));
    tester_handle_result(recordsDbAddRecord(rdb, "Come On Over", 1997, COUNTRY));
    tester_handle_result(recordsDbAddRecord(rdb, "Led Zeppelin II", 1969, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Appetite for Destruction", 1987, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Born in the U.S.A.", 1984, ROCK));

    print_msg("Add tracks");
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Smells Like Teen Spirit", 301));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "In Bloom", 254));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Come As You Are", 219));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Breed", 184));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Lithium", 257));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Polly", 177));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Nevermind", "Territorial Pissings", 143));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Hotel California", "Hotel California", 390));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Hotel California", "New Kid in Town", 325));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Hotel California", "Life in the Fast Lane", 251));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Led Zeppelin IV", "Black Dog", 296));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Led Zeppelin IV", "Rock and Roll", 220));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Led Zeppelin IV", "The Battle of Evermore", 350));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Led Zeppelin IV", "Stairway to Heaven", 482));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Led Zeppelin IV", "Misty Mountain Hop", 278));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Wall", "Another Brick in the Wall (Part 1)", 193));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Rumours", "Second Hand News", 150));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Rumours", "Dreams", 252));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Rumours", "Never Going Back Again", 138));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "Where the Streets Have No Name", 337));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "I Still Haven't Found What I'm Looking For", 294));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "With or Without You", 296));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky", 284));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Chronic", "Nuthin' but a 'G' Thang", 238));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Chronic", "Let Me Ride", 263));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Rocks Off", 259));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Rip This Joint", 136));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Tumbling Dice", 231));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Sweet Virginia", 267));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Torn and Frayed", 232));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Sweet Black Angel", 197));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Loving Cup", 256));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Happy", 190));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Exile on Main St.", "Turd on the Run", 120));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Hells Bells", 312));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Shoot to Thrill", 311));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "What Do You Do for Money Honey", 210));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Given the Dog a Bone", 210));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Let Me Put My Love into You", 205));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Back in Black", 255));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "You Shook Me All Night Long", 210));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Have a Drink on Me", 230));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Shake a Leg", 245));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Rock and Roll Ain't Noise Pollution", 252));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Thriller", "Wanna Be Startin' Somethin'", 386));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Thriller", "Baby Be Mine", 242));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "Welcome to the Jungle", 275));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "It's So Easy", 217));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "Nightrain", 265));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "Out ta Get Me", 254));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "Mr. Brownstone", 231));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "Paradise City", 406));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Appetite for Destruction", "My Michelle", 203));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Greatest Hits (1971-1975)", "Take It Easy", 187));
    
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Time", 421));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Money", 382));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Us and Them", 462));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Any Colour You Like", 205));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Brain Damage", 228));

    print_msg("Report ROCK records");
    tester_handle_result(recordsDbReportRecords(rdb, ROCK));

    print_msg("Report HIP HOP records");
    tester_handle_result(recordsDbReportRecords(rdb, HIP_HOP));

    print_msg("Remove Tracks");
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Joshua Tree", "With or Without You"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky"));

    print_msg("Report HIP HOP records");
    tester_handle_result(recordsDbReportRecords(rdb, HIP_HOP));

    print_msg("Remove Records");
    tester_handle_result(recordsDbRemoveRecord(rdb, "The Joshua Tree"));
    tester_handle_result(recordsDbRemoveRecord(rdb, "The Chronic"));

    print_msg("Report HIP HOP records");
    tester_handle_result(recordsDbReportRecords(rdb, HIP_HOP));

    recordsDbDestroy(rdb);
    printf("--------------\n");
}

void test2()
{
    print_msg("Test 22222");
    
    rdb = recordsDbCreate();
    if (rdb == NULL)
    {
        records_app_print_error_message(stderr, RDB_OUT_OF_MEMORY);
        exit(0);
    }

    print_msg("Add Records");
    tester_handle_result(recordsDbAddRecord(rdb, "The Joshua Tree", 1987, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "The Chronic", 1992, HIP_HOP));
    tester_handle_result(recordsDbAddRecord(rdb, "Exile on Main St.", 1972, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Back in Black", 1980, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Thriller", 1982, POP));
    tester_handle_result(recordsDbAddRecord(rdb, "Appetite for Destruction", 1897, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Appetite for Destruction", 1897, 30));

    print_msg("Add Tracks to 'The Joshua Tree'");
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "With or Without You", 296));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky", -308));

    print_msg("Add more Records");
    tester_handle_result(recordsDbAddRecord(rdb, "Thriller", 1982, POP));
    tester_handle_result(recordsDbAddRecord(rdb, "The Dark Side of the Moon", 1973, ROCK));

    print_msg("Add Tracks to 'The Dark Side of the Moon'");
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Speak to Me", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Breathe", 163));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "On the Run", 216));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "Time", 421));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Dark Side of the Moon", "The Great Gig in the Sky", 276));

    print_msg("Add Tracks to 'The Joshua Tree'");
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "With or Without You", 296));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky", 308));

    print_msg("'The Joshua Tree' Record");
    tester_handle_result(recordsDbRemoveRecord(rdb, "The Joshua Tree"));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "With or Without You", 296));
    tester_handle_result(recordsDbAddRecord(rdb, "The Joshua Tree", 1987, ROCK));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "With or Without You", 296));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky", 308));
    tester_handle_result(recordsDbReportTracksOfRecord(rdb, "The Joshua Tree"));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Back in Black", "Speak to Me", 90));
    tester_handle_result(recordsDbRemoveRecord(rdb, "Machina"));
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Speak to Me"));
    tester_handle_result(recordsDbReportRecords(rdb, JAZZ));

    print_msg("Remove Tracks");
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Joshua Tree", "With or Without You"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Joshua Tree", "Bullet the Blue Sky"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Joshua Tree", "With or Without You"));
    tester_handle_result(recordsDbReportTracksOfRecord(rdb, "The Joshua Tree"));

    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, NULL, "With or Without You"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "The Dark Side of the Moon", "with or Without You"));

    print_msg("Add generig Records");
    tester_handle_result(recordsDbAddRecord(rdb, "Record1", 1973, ROCK));
    tester_handle_result(recordsDbAddRecord(rdb, "Record2", 2022, JAZZ));
    tester_handle_result(recordsDbAddRecord(rdb, "Record3", 2004, JAZZ));
    tester_handle_result(recordsDbAddRecord(rdb, "Record4", 1999, BLUES));
    tester_handle_result(recordsDbAddRecord(rdb, "Record5", 1983, POP));
    tester_handle_result(recordsDbAddRecord(rdb, "Record6", 1932, ROCK));

    print_msg("Add Generic Tracks");
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record1", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record1", "Track2", 163));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record1", "Track3", 216));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record1", "Track4", 421));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record1", "Track5", 276));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record2", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record2", "Track2", 163));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record3", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record3", "Track2", 163));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record3", "Track3", 216));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record3", "Track4", 421));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record3", "Track5", 276));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record4", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record4", "Track2", 163));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record5", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record5", "Track2", 163));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record5", "Track3", 216));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record5", "Track4", 421));

    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record6", "Track1", 90));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record6", "Track2", 163));
    tester_handle_result(recordsDbAddTrackToRecord(rdb, "Record6", "Track3", 216));

    print_msg("Remove Tracks");
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record1", "Track4"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record1", "Track5"));

    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record2", "Track1"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record2", "Track2"));

    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record3", "Track1"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record3", "Track2"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record3", "Track3"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record3", "Track4"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record3", "Track5"));

    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record5", "Track1"));
    tester_handle_result(recordsDbRemoveTrackFromRecord(rdb, "Record5", "Track2"));

    print_msg("Remove Records");
    tester_handle_result(recordsDbRemoveRecord(rdb, "Record4"));
    tester_handle_result(recordsDbRemoveRecord(rdb, "Record2"));

    print_msg("Report BLUES Records");
    tester_handle_result(recordsDbReportRecords(rdb, BLUES));

    print_msg("Report Containing Records");
    printf("Track1\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track1"));
    printf("Track2\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track2"));
    printf("Track3\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track3"));
    printf("Track4\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track4"));
    printf("Track5\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track5"));
    printf("Track6\n");
    tester_handle_result(recordsDbReportContainingRecords(rdb, "Track6"));

    print_msg("Print all Records");
    tester_handle_result(recordsDbReportRecords(rdb, ALL_CATEGORIES));

    recordsDbDestroy(rdb);
}

int main()
{
#ifdef TEST1
    test1();
#elif defined TEST2
    test2();
#endif
    return 0;
}