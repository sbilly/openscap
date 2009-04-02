/*
 * oval_behavior.c
 *
 *  Created on: Mar 3, 2009
 *      Author: david.niemoller
 */
#include <stdlib.h>
#include <stdio.h>
#include "oval_definitions_impl.h"
#include "oval_collection_impl.h"
#include "oval_string_map_impl.h"

typedef struct oval_behavior {
	struct oval_value *value;
	struct oval_string_map *att_values;
} oval_behavior_t;

int oval_iterator_behavior_has_more(struct oval_iterator_behavior *oc_behavior)
{
	return oval_collection_iterator_has_more((struct oval_iterator *)
						 oc_behavior);
}

struct oval_behavior *oval_iterator_behavior_next(struct oval_iterator_behavior
						  *oc_behavior)
{
	return (struct oval_behavior *)
	    oval_collection_iterator_next((struct oval_iterator *)oc_behavior);
}

struct oval_value *oval_behavior_value(struct oval_behavior *behavior)
{
	return (behavior)->value;
}

struct oval_iterator_string *oval_behavior_attribute_keys(struct oval_behavior
							  *behavior)
{
	return (struct oval_iterator_string *)oval_string_map_keys(behavior->
								   att_values);
}

char *oval_behavior_value_for_key(struct oval_behavior *behavior,
				  char *attributeKey)
{
	return (char *)oval_string_map_get_value(behavior->att_values,
						 attributeKey);
}

struct oval_behavior *oval_behavior_new()
{
	oval_behavior_t *behavior =
	    (oval_behavior_t *) malloc(sizeof(oval_behavior_t));
	behavior->value = NULL;
	behavior->att_values = oval_string_map_new();
	return behavior;
}

void oval_behavior_free(struct oval_behavior *behavior)
{
	void free_value(void *value) {
		oval_value_free(behavior->value);
	}
	if (behavior->value != NULL)
		free_value((void *)behavior->value);
	oval_string_map_free(behavior->att_values, &free_value);
	free(behavior);
}

void set_oval_behavior_value_for_key(struct oval_behavior *behavior,
				     struct oval_value *value, char *key)
{
	oval_string_map_put(behavior->att_values, key, (void *)value);
}

char *_oval_behavior_unix_fields[] = {
	"max_depth",
	"recurse",
	"recurse_direction",
	"recurse_file ystem",
	NULL
};

//typedef void (*oval_behavior_consumer)(struct oval_behavior_node *, void*);
int oval_behavior_parse_tag(xmlTextReaderPtr reader,
			    struct oval_parser_context *context,
			    oval_family_enum family,
			    oval_behavior_consumer consumer, void *user)
{
	struct oval_behavior *behavior = oval_behavior_new();
	char **fields;
	switch (family) {
	case FAMILY_UNIX:
		fields = _oval_behavior_unix_fields;
		break;
	default:
		fields = NULL;
	}

	if (fields == NULL) {
		printf
		    ("NOTICE::oval_behavior_parse_tag:: No behavior fields registered for family %d\n",
		     family);
	} else {
		int i;
		for (i = 0; fields[i] != NULL; i++) {
			char *name = fields[i];
			char *value = xmlTextReaderGetAttribute(reader, name);
			if (value != NULL) {
				oval_string_map_put(behavior->att_values, name,
						    (void *)value);
			}
		}
	}
	(*consumer) (behavior, user);
	return 1;
}

void oval_behavior_to_print(struct oval_behavior *behavior, char *indent,
			    int index)
{
	if (strlen(indent) > 80)
		indent = "....";
	char nxtindent[200];
	*nxtindent = 0;
	strcat(nxtindent, indent);
	if (index == 0)
		strcat(nxtindent, "BEHAVIOR.");
	else {
		strcat(nxtindent, "BEHAVIOR[");
		char itoad[10];
		*itoad = 0;
		itoa(index, itoad, 10);
		strcat(nxtindent, itoad);
		strcat(nxtindent, "].");
	}

	struct oval_iterator_string *keys =
	    oval_behavior_attribute_keys(behavior);
	if (oval_iterator_string_has_more(keys)) {
		int index;
		for (index = 1; oval_iterator_string_has_more(keys); index++) {
			char *key = oval_iterator_string_next(keys);
			char *val = oval_behavior_value_for_key(behavior, key);
			printf("%s%s = [%s]\n", nxtindent, key, val);
		}
	} else {
		printf("%s <<NO FIELDS BOUND TO BEHAVIOR>>\n", nxtindent);
	}
}
