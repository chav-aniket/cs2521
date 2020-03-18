#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "invertedIndex.h"
#include "tfidf.h"
#include "BSTree.h"

TfIdfList newList(char *filename, double tfidf) {
	TfIdfList new = malloc(sizeof(*new));
	new->filename = malloc(sizeof(char) * 101);
	strcpy(new->filename, filename);
	new->tfidf_sum = tfidf;
	new->next = NULL;
	return new;
}

/*TfIdfList tfidfInsert(TfIdfList head, char *filename, double tfidf) {
	TfIdfList new = newList(filename, tfidf);
	if (head == NULL) {
		head = new;
	} else if (new->tfidf_sum > head->tfidf_sum) {
		new->next = head;
		head = new;
	} else if (new->tfidf_sum == head->tfidf_sum) {
		if (strcmp(new->filename, head->filename) > 0) {
			new->next = head->next;
			head->next = new;
		} else {
			new->next = head;
			head = new;
		}
	} else {
		TfIdfList curr = head;
		TfIdfList prev = NULL;
		while (curr != NULL && new->tfidf_sum < curr->tfidf_sum) {
			prev = curr;
			curr = curr->next;
		}
		prev->next = new;
		new->next = curr;
	}
	return head;
}*/

TfIdfList tfidfInsert(TfIdfList head, char *filename, double tfidf) {
	TfIdfList new = newList(filename, tfidf);
	if (head == NULL) {
		head = new;
	} else if (new->tfidf_sum > head->tfidf_sum) {
		new->next = head;
		head = new;
	} else if (new->tfidf_sum == head->tfidf_sum) {
		if (strcmp(new->filename, head->filename) > 0) {
			new->next = head->next;
			head->next = new;
		} else {
			new->next = head;
			head = new;
		}
	} else {
		TfIdfList curr = head;
		TfIdfList prev = NULL;
		if (isTfIdfUnique(head, tfidf)) {
			while (curr->next != NULL) {
				if (curr->tfidf_sum >= new->tfidf_sum &&
					curr->next->tfidf_sum < new->tfidf_sum) {
						new->next = curr->next;
						curr->next = new;
						break;
					}
				curr = curr->next;
			}
			curr->next = new;
		} else {
			while (curr != NULL && new->tfidf_sum != curr->tfidf_sum) {
				prev = curr;
				curr = curr->next;
			}
			while (curr != NULL && new->tfidf_sum == curr->tfidf_sum &&
					strcmp(new->filename, curr->filename) > 0) {
				prev = curr;
				curr = curr->next;
			}
			new->next = curr;
			prev->next = new;
		}
	}
	return head;
}

double tfidfCalc(int D, double Appearances, FileList node) {
	double totalDocs = D;

	return (node->tf * (log10(totalDocs/Appearances)));
}

TfIdfList isTfIdfAdded(TfIdfList head, char *filename) {
	TfIdfList curr = head;
	while (curr != NULL) {
		if (strcmp(curr->filename, filename) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

int isTfIdfUnique(TfIdfList head, double tfidf) {
	TfIdfList curr = head;
	while (curr != NULL) {
		if (curr->tfidf_sum == tfidf) {
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

void freeTfIdfList(TfIdfList head) {
	TfIdfList curr = head;
	TfIdfList tmp = head;
	while(curr != NULL) {
		tmp = curr;
		curr = curr->next;
		free(tmp->filename);
		free(tmp);
	}
}

TfIdfList orderList(TfIdfList head) {
	TfIdfList newHead = NULL;
	TfIdfList curr = head;
	while (curr != NULL) {
		newHead = tfidfInsert(newHead, curr->filename, curr->tfidf_sum);
		curr = curr->next;
	}
	return newHead;
}
