# makefile for the movie reviews assignment

# The compiler we'll be using
CC = gcc

# Standard compiler switches used in the course
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O1

# Linker swithces, we'll always link the math library since it is commonly needed
LDFLAGS = -lm

# When you type "make", it will default to trying to build all the rules in this list
# TODO 1: Add ScoreWords to the default rule
default: TestReview TestReviews ScoreWords

# To build just the TestReview executable, type "make TestReview"
# This gcc command compiles TestReivew.c and links in the object code for Review
# Since this rule depends on the Review.o rule, that rule will get executed if needed
TestReview: TestReview.c Review.o
	${CC} ${CFLAGS} TestReview.c Review.o -o TestReview ${LDFLAGS}

# To build just the TestReview executable, type "make TestReviews"
TestReviews: TestReviews.c Reviews.o Review.o
	${CC} ${CFLAGS} TestReviews.c Reviews.o Review.o -o TestReviews ${LDFLAGS}

# TODO 2: Add new rule to build the ScoreWords executable
ScoreWords: ScoreWords.c Reviews.o Review.o
	${CC} ${CFLAGS} ScoreWords.c Reviews.o Review.o -o ScoreWords ${LDFLAGS}

# Builds just the object file for the Review data type (this is what the -c does)
Review.o: Review.c Review.h
	${CC} ${CFLAGS} -c Review.c

# Builds just the object file for the Review data type (this is what the -c does)
Reviews.o: Reviews.c Reviews.h
	${CC} ${CFLAGS} -c Reviews.c

# TODO 3: Add your new executable to the list of things that get deleted on "make clean"
clean: 
	rm -f TestReview TestReviews ScoreWords *.o
