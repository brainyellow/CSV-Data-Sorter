#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sorter.h"
#include "mergesort.c"

int main(int argc, char * argv[])
{

	//Checking if argv[1] has an input
	if (argv[1] == 0)
	{
		printf("-c not entered\n");
		return -1;
	}
	//Checking if argv[1] is -c
	if (strcmp(argv[1],"-c") != 0)
	{
		printf("Did not enter -c\n");
		return -1;
	}
	//Checking if argv[2] has an input
	if (argv[2] == 0)
	{
		printf("Did not enter header column input\n");
		return -1;
	}

	struct freeNode *head = malloc(sizeof(struct freeNode));
	head->freePtr = NULL;
	struct freeNode* newFree;

	//size of CSV
	size_t sizeCSV = 1000;
	char* CSV = malloc(sizeof(char)*sizeCSV);
	void* freeCSV = CSV;
	
	//stores size of trimBuffer
	size_t sizeTrimBuffer = 50;
	char* trimBuffer = malloc(sizeof(char)*sizeTrimBuffer);
	
	//tokens
	char* tempStr;	
	char* fronttoken;
	char* token;
	char* backtoken;
	char* title;
	
	//size of initial malloc for Movie array
	size_t sizeMovies = 1000;
	
	//allocate mem for array of movie structs
	struct Movie* movies = malloc(sizeof(struct Movie)*sizeMovies);

	//compare each token to user input (argv[2]) with headerFlag
	int headerFlag = 0;
	
	//counter and variable to keep track of which column to sort by
	int sortColumnCounter = 0;
	int columnToSort = 0;
	//get first line (headers)
	fgets(CSV, sizeof(char)*sizeCSV,stdin);
	//tokenize first row using comma delim
	token = strtok(CSV, ",");
	while(token != NULL)
	{	
		//assigning headers to a movie struct to print later
		if (sortColumnCounter < 27)
			printf("%s,", token);
		if (sortColumnCounter == 27)
			printf("%s", token);
		//compare header tokens with user defined sort parameter
		if(strcmp(token, argv[2])== 0)
		{
			headerFlag = 1;
			columnToSort = sortColumnCounter;
		}

		token = strtok(NULL, ",");
		sortColumnCounter++;
	}

	//return -1 if match not found
	if(headerFlag == 0)
	{
		printf("Did not enter correct column header\n");
		return -1;	
	}


	//counter for current struct in movies[]
	int i = 0;	
	//counter for current location in individual struct
	int n = 0;

	void* freetempStr;
	while(fgets(CSV, sizeof(char)*sizeCSV,stdin))
	{	
		//reallocs when i counter is larger than size of initial movies malloc
		if (i >= sizeMovies)
		{
			//add 1000 movies to size of movies array
			sizeMovies += 1000;		//adding 1000 movies to size of movies array
			movies = realloc(movies, sizeof(struct Movie)*sizeMovies);
			
			//exception if realloc returns NULL
			if (movies == NULL)
			{
				printf("Realloc failed, not enough memory\n");
				return -1; 			
			}
		}
		
		//dups CSV line
		tempStr = strdup(CSV); 

		//tempStr = malloc(sizeof(strlen(CSV)+1));
		freetempStr = tempStr;
		//strcpy(tempStr, CSV);
		
		freecounter++;
		if(head->freePtr == NULL)
		{
			head->freePtr = freetempStr;
			head->next = NULL;
		}
		else
		{
			struct freeNode* newFree = malloc(sizeof(struct freeNode));
			newFree->freePtr = freetempStr;
			newFree->next = head;
			head = newFree;
		}

		//stores line until first quote
		fronttoken = strsep(&tempStr, "\"");
		//stores line from first quote > second quote
		title = strsep(&tempStr, "\"");
		//stores line from second quote > newline
		backtoken = strsep(&tempStr, "\n");

		if(fronttoken != NULL)
		{
			//tempStr = strdup(fronttoken);
			tempStr = malloc(strlen(fronttoken)+1);
			freetempStr = tempStr;

			newFree = malloc(sizeof(struct freeNode));
			newFree->freePtr = freetempStr;
			newFree->next = head;
			head = newFree;

			strcpy(tempStr, fronttoken);
			//reallocing trimBuffer based on size of fronttoken. Since fronttoken is sometimes the whole line, it will be largest possible string to store
			while(strlen(tempStr) >= sizeTrimBuffer)		
			{	//doubling size until larger than fronttoken
				sizeTrimBuffer += 100;
				trimBuffer = realloc(trimBuffer, sizeof(char)*sizeTrimBuffer);
				//if not enough mem
				if(trimBuffer == NULL)
				{
					printf("Not enough memory\n");
					return -1;
				}
			}
			/*
			* trimming leading and trailing whitespace for fronttoken because if there is leading whitespace in front of title,
			* fronttoken will have trailing whitespace, which causes extra comma to persist
			*/
			strcpy(trimBuffer, tempStr);									
			strcpy(tempStr, trim(trimBuffer));

			//deleting extra comma to avoid creating extra token
			if (title != NULL)
			{
				tempStr[strlen(tempStr) - 1] = 0;
			}
			
			//tokenize fronttoken using comma delim
			token = strsep(&tempStr, ",");
			while(token != NULL)
			{
				//trimming whitespace in token
				strcpy(trimBuffer, token);
				strcpy(token, trim(trimBuffer));
				//if statements to place current token in correct struct variable
				//Includes all variables
				if(n == 0)
					movies[i].color = token;
				if(n == 1)
					movies[i].director_name = token;
				if(n == 2)
					movies[i].num_critic_for_reviews = token;
				if(n == 3)
					movies[i].duration = token;
				if(n == 4)
					movies[i].director_facebook_likes = token;
				if(n == 5)
					movies[i].actor_3_facebook_likes = token;
				if(n == 6)
					movies[i].actor_2_name = token;
				if(n == 7)
					movies[i].actor_1_facebook_likes = token;
				if(n == 8)
					movies[i].gross = token;
				if(n == 9)
					movies[i].genres = token;
				if(n == 10)
					movies[i].actor_1_name = token;
				if(n == 11)
					movies[i].movie_title = token;
				if(n == 12)
					movies[i].num_voted_users = token;
				if(n == 13)
					movies[i].cast_total_facebook_likes = token;
				if(n == 14)
					movies[i].actor_3_name = token;
				if(n == 15)
					movies[i].facenumber_in_poster = token;
				if(n == 16)
					movies[i].plot_keywords = token;
				if(n == 17)
					movies[i].movie_imdb_link = token;
				if(n == 18)
					movies[i].num_user_for_reviews = token;
				if(n == 19)
					movies[i].language = token;
				if(n == 20)
					movies[i].country = token;
				if(n == 21)
					movies[i].content_rating = token;
				if(n == 22)
					movies[i].budget = token;
				if(n == 23)
					movies[i].title_year = token;
				if(n == 24)
					movies[i].actor_2_facebook_likes = token;
				if(n == 25)
					movies[i].imdb_score = token;
				if(n == 26)
					movies[i].aspect_ratio = token;
				if(n == 27)
					movies[i].movie_facebook_likes = token;
				token = strsep(&tempStr, ",");
				n++;
			}
		}
		//Only tokenize backtoken if NOT NULL
		if(backtoken != NULL)
		{
			//tempStr = strdup(backtoken);
			tempStr = malloc(strlen(backtoken)+1);
			freetempStr = tempStr;

			newFree = malloc(sizeof(struct freeNode));
			newFree->freePtr = freetempStr;
			newFree->next = head;
			head = newFree;

			strcpy(tempStr,backtoken);
			if(title != NULL)
			{
				strcpy(trimBuffer, title);
				strcpy(title, trim(trimBuffer));
				//if statements to place current token in correct struct variable
				//Only including title variable
				if(n == 11)
					movies[i].movie_title = title;
				n++;
			}
			if(title != NULL)
				strsep(&tempStr, ","); //getting rid of extra comma from title

			token = strsep(&tempStr, ",");
			while(token != NULL)
			{
				//trimming whitespace
				strcpy(trimBuffer, token);
				strcpy(token, trim(trimBuffer));
				//if statements to place current token in correct struct variable
				//Only includes variables after movie title	
				if(n == 12)
					movies[i].num_voted_users = token;
				if(n == 13)
					movies[i].cast_total_facebook_likes = token;
				if(n == 14)
					movies[i].actor_3_name = token;
				if(n == 15)
					movies[i].facenumber_in_poster = token;
				if(n == 16)
					movies[i].plot_keywords = token;
				if(n == 17)
					movies[i].movie_imdb_link = token;
				if(n == 18)
					movies[i].num_user_for_reviews = token;
				if(n == 19)
					movies[i].language = token;
				if(n == 20)
					movies[i].country = token;
				if(n == 21)
					movies[i].content_rating = token;
				if(n == 22)
					movies[i].budget = token;
				if(n == 23)
					movies[i].title_year = token;
				if(n == 24)
					movies[i].actor_2_facebook_likes = token;
				if(n == 25)
					movies[i].imdb_score = token;
				if(n == 26)
					movies[i].aspect_ratio = token;
				if(n == 27)
					movies[i].movie_facebook_likes = token;
				
				token = strsep(&tempStr, ",");
				n++;
			}
			//free(freetempStr);
		}
		//resetting n after each line
		n = 0;
		//incrementing i movies
		i++;
	}
	
	int structCount = i;
	
	//Sort the movies array using the mergesort function
	mergesort(columnToSort, movies, 0, structCount - 1);

	//Output data by looping through all structs
	//Use new counter to increment through structs
	int k = 0;
	while(k < i )
	{
		printf("%s,", movies[k].color);
		printf("%s,", movies[k].director_name);
		printf("%s,", movies[k].num_critic_for_reviews);
		printf("%s,", movies[k].duration);
		printf("%s,", movies[k].director_facebook_likes);
		printf("%s,", movies[k].actor_3_facebook_likes);
		printf("%s,", movies[k].actor_2_name);
		printf("%s,", movies[k].actor_1_facebook_likes);
		printf("%s,", movies[k].gross);
		printf("%s,", movies[k].genres);
		printf("%s,", movies[k].actor_1_name);
		printf("\"%s\",", movies[k].movie_title);
		printf("%s,", movies[k].num_voted_users);
		printf("%s,", movies[k].cast_total_facebook_likes);
		printf("%s,", movies[k].actor_3_name);
		printf("%s,", movies[k].facenumber_in_poster);
		printf("%s,", movies[k].plot_keywords);
		printf("%s,", movies[k].movie_imdb_link);
		printf("%s,", movies[k].num_user_for_reviews);
		printf("%s,", movies[k].language);
		printf("%s,", movies[k].country);
		printf("%s,", movies[k].content_rating);
		printf("%s,", movies[k].budget);
		printf("%s,", movies[k].title_year);
		printf("%s,", movies[k].actor_2_facebook_likes);
		printf("%s,", movies[k].imdb_score);
		printf("%s,", movies[k].aspect_ratio);
		printf("%s,", movies[k].movie_facebook_likes);
		printf("\n");
		k++;
	}

	while(head != NULL)
	{
		struct freeNode* old = head;
		free(head->freePtr);
		head = head->next;
		free(old);
	}
	
	//freeing mallocs	
	free(freeCSV);
	free(trimBuffer);
	free(tempStr);
	free(movies);
	
	return 0;
}
//function for trimming whitespace, accepts and returns char*
char* trim(char *str) 
{
    char* end = str + strlen(str) - 1;
    while(*str && isspace(*str)) str++;
    while(end > str && isspace(*end)) *end-- = '\0';
    return str;
}
