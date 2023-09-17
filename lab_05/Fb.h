// Friendbook ADT
// For  simplicity,  people are identified by their names, so two people
// cannot share the same name.

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef FB_H
#define FB_H

#include "List.h"

typedef struct fb *Fb;

////////////////////////////////////////////////////////////////////////

/**
 * Creates a new instance of Friendbook
 */
Fb   FbNew(void);

/**
 * Frees all memory allocated to the given Friendbook instance
 */
void FbFree(Fb fb);

/**
 * Returns the number of people who have been added to Friendbook.
 */
int  FbNumPeople(Fb fb);

/**
 * Creates  a  Friendbook  account for the given person. Returns true if
 * successful, and false if a person with that name already exists.
 */
bool FbAddPerson(Fb fb, char *name);

/**
 * Returns  true  if  the given person has been added to Friendbook, and
 * false otherwise.
 */
bool FbHasPerson(Fb fb, char *name);

/**
 * Returns a list of all people who have been added to Friendbook.
 */
List FbGetPeople(Fb fb);

/**
 * Friends two people. Assumes that they both have a Friendbook account,
 * and  that they are not the same person. Returns true if the operation
 * was successful, and false if they were already friends.
 */
bool FbFriend(Fb fb, char *name1, char *name2);

/**
 * Checks  whether two people are friends. Assumes that they both have a
 * Friendbook account. Returns  true  if  they are  friends,  and  false
 * otherwise.
 */
bool FbIsFriend(Fb fb, char *name1, char *name2);

////////////////////////////////////////////////////////////////////////
// Your tasks

/**
 * Returns  the number of friends the given person has. Assumes that the
 * person has a Friendbook account.
 */
int  FbNumFriends(Fb fb, char *name);

/**
 * Unfriends  two  people.  Assumes  that  they  both  have a Friendbook
 * account, and that they are not the same person. Returns true  if  the
 * operation was successful, and false if the people were not friends.
 */
bool FbUnfriend(Fb fb, char *name1, char *name2);

/**
 * Returns  a list of the names of all the mutual friends of two people.
 * Assumes that the people have been added to Friendbook, and that  they
 * are not the same person.
 */
List FbMutualFriends(Fb fb, char *name1, char *name2);

/**
 * Generates  friend recommendations for a person and stores them in the
 * given recs array. Returns the number of recommendations stored.
 *
 * This function should only recommend people who are friends of friends
 * of the given person.  In other words, it should only recommend people
 * who share at least one mutual friend with the person.  Obviously,  it
 * should not recommend someone who is already the person's friend.
 * 
 * It  is  possible  for there to be no recommendations if, for example,
 * the person is already friends with everyone.
 *
 * Each recommendation consists of the name of a person and  the  number
 * of mutual friends they share with the given person.
 *
 * Recommendations should be sorted in descending order on the number of
 * mutual friends shared.  If two people share the same number of mutual
 * friends, they may be sorted in any order.
 */
struct recommendation {
	char *name;
	int numMutualFriends;
};

int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]);

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Generates recommendations for a person based on friend closeness.
 * Returns a list of the names of all the recommended friends.
 *
 * Friends of friends should  be  recommended first, followed by friends
 * of friends of friends, and so on. People who are the same  "distance"
 * from the given person can be recommended in any order.
 *
 * Generate  a  maximum of 20 recommendations. If there are more than 20
 * recommendations, ignore the rest.
 */
List FbFriendRecs2(Fb fb, char *name);

#endif

