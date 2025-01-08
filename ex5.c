#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

#define WATCH_PLAYLISTS 1
#define ADD_PLAYLIST 2
#define REMOVE_PLAYLIST 3
#define EXIT_MAIN_MENU 4
#define SHOW_PLAYLIST 1
#define ADD_SONG 2
#define DELETE_SONG 3
#define SORT 4
#define PLAY 5
#define EXIT_PLAYLIST 6
void freeSong(Song* song) {
    if(song){
    free(song->title);
    free(song->artist);
    free(song->lyrics);
    free(song);
    }
}
void freePlaylist(Playlist* playlist) {
    if(playlist == NULL)
        return;
    for (int i = 0; i< playlist->songsNum; i++){
        freeSong(playlist->songs[i]);
    }
    if(playlist->songsNum > 0)
    {
        free(playlist->songs);
        free(playlist->name);
    }
}
void freePlaylists(Playlist* playlists, int current_size){
    for (int i = 0; i < current_size; i++){
        freePlaylist(&(playlists[i]));
    }
}


void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}
void sortByYear(Playlist* playlist){
    for (int i = 0; i < playlist->songsNum - 1; i++)
        {
            for(int j = i+1; j < playlist->songsNum; j++)
            {
                if(playlist->songs[i]->year < playlist->songs[j]->year)
                {
                    Song* temp = playlist->songs[i];
                    playlist->songs[i] = playlist->songs[j];
                    playlist->songs[j] = temp;
                }
            }
        }
}
void sortByStreamsAscending(Playlist* playlist){
    for (int i = 0; i < playlist->songsNum - 1; i++)
        {
            for(int j = i+1; j < playlist->songsNum; j++)
            {
                if(playlist->songs[i]->streams > playlist->songs[j]->streams)
                {
                    Song* temp = playlist->songs[i];
                    playlist->songs[i] = playlist->songs[j];
                    playlist->songs[j] = temp;
                }
            }
        }
}
void sortByStreamsDescending(Playlist* playlist){
    for (int i = 0; i < playlist->songsNum - 1; i++)
        {
            for(int j = i+1; j < playlist->songsNum; j++)
            {
                if(playlist->songs[i]->streams < playlist->songs[j]->streams)
                {
                    Song* temp = playlist->songs[i];
                    playlist->songs[i] = playlist->songs[j];
                    playlist->songs[j] = temp;
                }
            }
        }
}
void sortByAlphabetical(Playlist* playlist){
    for (int i = 0; i < playlist->songsNum - 1; i++)
        {
            for(int j = i+1; j < playlist->songsNum; j++)
            {
                if(strcmp(playlist->songs[i]->title, playlist->songs[j]->title) > 0)
                {
                    Song* temp = playlist->songs[i];
                    playlist->songs[i] = playlist->songs[j];
                    playlist->songs[j] = temp;
                }
            }
        }
}
void sortPlaylist(Playlist* playlist) {
    printf("choose:\n1. sort by year\n2. sort by streams - ascending order\n3. sort by streams - descending order\n4. sort alphabetically\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        // Sort by year
        sortByYear(playlist);
        break;
    case 2:
        // Sort by streams - ascending order
        sortByStreamsAscending(playlist);
        break;
    case 3:
        // Sort by streams - descending order
        sortByStreamsDescending(playlist);
        break;
    case 4:
        // Sort alphabetically
        sortByAlphabetical(playlist);
    default:
        printf("Invalid option, sorted by alphabetical order\n");
        sortByAlphabetical(playlist);
        break;
    }
    printf("sorted\n");
}
char* getString(){
    char* str = (char*)malloc(sizeof(char));
    int size = 1;
    char ch;
    do
    {
        ch = getchar();
    } while (ch == '\n' || ch == ' ');
    
    while (ch != '\n' && ch != '\0'){
            str[size - 1] = ch;
            size++;
            str = (char*)realloc(str, size*sizeof(char));
            ch = getchar();
    }
    str[size-1] = '\0';
    return str;
}
void playSong(Playlist* playlist, int currentlyPlaying){
        printf("Now playing %s\n", playlist->songs[currentlyPlaying]->title);
        printf("$ %s $\n", playlist->songs[currentlyPlaying]->lyrics);
        printf("\n");
        playlist->songs[currentlyPlaying]->streams++;
}
//Show the list of playlists
void printPlaylists(Playlist* playlists, int numPlaylists) {
    int i = 0;
    printf("Choose a playlist:\n");
    while (i < numPlaylists) 
    {
        printf("\t%d. %s\n", i + 1, playlists[i].name);
        i++;
    }
    printf("\t%d. Back to main menu\n", i+1);
}
void chooseSong(Playlist* playlist)
{
    if(playlist->songsNum == 0){
        printf("No songs in playlist\n");
        return;
    }

    int choice = 1;
    while (choice != 0){
    printf("choose a song to play, or 0 to quit:\n");
    scanf("%d", &choice);
    if (choice == 0)
        return;
    playSong(playlist, choice - 1);
    }
}
void showPlaylist(Playlist* playlist){
    for(int i = 1; i <= playlist->songsNum; i++){
    printf("%d. Title: %s\n", i, playlist->songs[i-1]->title);
    printf("\tArtist: %s\n", playlist->songs[i-1]->artist);
    printf("\tReleased: %d\n", playlist->songs[i-1]->year);
    printf("\tStreams: %d\n", playlist->songs[i-1]->streams);
    printf("\n");
    }

}
void addSong(Playlist* playlist){
    printf("Enter song details\n");
    playlist->songs = (Song**)realloc(playlist->songs, (playlist->songsNum+1)*sizeof(Song*));
    playlist->songs[playlist->songsNum] = (Song*)malloc(sizeof(Song));
    printf("Title:\n");
    playlist->songs[playlist->songsNum]->title = getString();
    printf("Artist:\n");
    playlist->songs[playlist->songsNum]->artist = getString();
    printf("Year of release:\n");
    scanf("%d", &playlist->songs[playlist->songsNum]->year);
    printf("Lyrics:\n");
    playlist->songs[playlist->songsNum]->lyrics = getString();
    playlist->songs[playlist->songsNum]->streams = 0;
    playlist->songsNum++;
}
void deleteSong(Playlist* playlist){
    printf("choose a song to delete, or 0 to quit:\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 0)
    {
        return;
    }
    //free the song that was chosen to be deleted
    freeSong(playlist->songs[choice-1]);
    //Start from the song we wish to delete and move all the songs one place backwards in the array and override it
    for (int i = choice-1; i < playlist->songsNum-1; i++)
        playlist->songs[i] = playlist->songs[i+1];

    //reduce the song counter by one
    playlist->songsNum--;
    if(playlist->songsNum > 0)
    {
        Song** temp = (Song**)realloc(playlist->songs, (playlist->songsNum) * sizeof(Song));
        if(temp != NULL)
            playlist->songs = temp;
        else
        {
            free(playlist->songs);
            playlist->songs = NULL;
        }
    }
}

void playFullPlaylist(Playlist* playlist){
    for (int currentlyPlaying = 0; currentlyPlaying < playlist->songsNum; currentlyPlaying++)
        playSong(playlist, currentlyPlaying);
}
void choosePlaylist(Playlist* playlist){
    printf("playlist %s\n", playlist->name);
    int choice = 0;
    while (choice != EXIT_PLAYLIST)
    {
        printf("\t1. Show Playlist\n\t2. Add song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case SHOW_PLAYLIST:
                showPlaylist(playlist);
                chooseSong(playlist);
                break;
            case ADD_SONG:
                addSong(playlist);
                break;
            case DELETE_SONG:
                showPlaylist(playlist);
                deleteSong(playlist);
                break;
            case SORT:
                sortPlaylist(playlist);
                break;
            case PLAY:
                playFullPlaylist(playlist);
                break;
            case EXIT_PLAYLIST:
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    }

}
void addPlaylist(Playlist** playlists, int* numPlaylists, int* current_size) {
    if(*numPlaylists >= *current_size)
    {
        *current_size = *current_size + 1;
        Playlist * temp = (Playlist*)realloc(*playlists, (*current_size)*sizeof(Playlist));
        if (temp == NULL)
            exit(1);
        *playlists = temp;
    }
    printf("Enter playlist's name:\n");
    // Initialize the new playlist
    (*playlists)[*numPlaylists].name = getString();
    (*playlists)[*numPlaylists].songs = (Song**)malloc(1*sizeof(Song*));
    (*playlists)[*numPlaylists].songsNum = 0;
    *numPlaylists = *numPlaylists + 1;
}
void removePlaylist(Playlist** playlists, int* numPlaylists, int* current_size){
    int choice;
    scanf("%d", &choice);

    //free the playlist that was chosen to be deleted
    freePlaylist(&((*playlists)[choice-1]));
    *current_size = *current_size - 1;
    //iterate over the playlists array starting from the playlist we wish to delete and move all the playlists one place backwards in the array and override it
    for (int i = choice-1; i < *current_size; i++)
    {   
        (*playlists)[i] = (*playlists)[i+1];
    }
    *numPlaylists = *numPlaylists - 1;
    if(*numPlaylists == 0)
    {
        if(*playlists != NULL)
            free(*playlists);
        *playlists = NULL;
        *current_size = 0;
    }
    else
    {
        //validate it isn't a NULL
        Playlist* temp = (Playlist*)realloc(*playlists, (*current_size) * sizeof(Playlist));
        if(temp == NULL)
            exit(1);
        *playlists = temp;
    }


}


int main() {
    int current_size = 1;
    Playlist* playlists = (Playlist*)malloc(current_size*sizeof(Playlist));
    int numPlaylists = 0;
    int choice = 0;
    while(choice != EXIT_MAIN_MENU){
        printPlaylistsMenu();
        scanf("%d", &choice);
        switch (choice)
            {
            case WATCH_PLAYLISTS:
                printPlaylists(playlists, numPlaylists);
                int playlistChoice;
                scanf("%d", &playlistChoice);
                //if return to main menu was chosen
                if (playlistChoice >= numPlaylists + 1)
                    break;
                choosePlaylist(&playlists[playlistChoice-1]);
                break;
            case ADD_PLAYLIST:
                if(current_size == 0)
                {
                    current_size = 1;
                    playlists = (Playlist*)malloc(current_size*sizeof(Playlist));
                }
                addPlaylist(&playlists, &numPlaylists, &current_size);
                break;
            case REMOVE_PLAYLIST:
                printPlaylists(playlists, numPlaylists);
                removePlaylist(playlists, &numPlaylists, &current_size);
                break;
            case EXIT_MAIN_MENU:
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    }
    if(playlists != NULL)
    {
        freePlaylists(playlists, current_size);
        free(playlists);
    }
    printf("Goodbye!\n");
    return 0;
}
