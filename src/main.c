#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"

#define IND_DEP 2
#define INDENT(n) if ((n) > 0) printf("%*s", (n), " ")

char *slurp_text(FILE *fp);
void print_json(cJSON *json, int indent);


int main(int argc, char const *argv[])
{
    FILE *fp = stdin;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }

    char *json_str = slurp_text(fp);
    if (argc > 1)
        fclose(fp);

    if (json_str)
    {
        const char *parse_end = NULL;
        cJSON *json = cJSON_ParseWithOpts(json_str, &parse_end, 0);
        if (json == NULL)
        {
            if (parse_end != NULL)
            {
                fprintf(stderr, "Error before: %s\n", parse_end);
            }
            exit(EXIT_FAILURE);
        }
        free(json_str);
        json_str = NULL;

        print_json(json, 0);
    }

    exit(EXIT_SUCCESS);
}

char *slurp_text(FILE *fp) {
    char *content = NULL;
    size_t len = 0;
    if (getdelim(&content, &len, '\0', fp) == -1) {
        perror("getdelim");
        free(content);
        return 0;
    }
    return content;
}

void print_json(cJSON *json, int indent) {
    if (!json) {
        fputs("Cannot print NULL cJSON object", stderr);
    } else if (cJSON_IsBool(json)) {
        printf("%s\n", cJSON_IsTrue(json) ? "True" : "False");
    } else if (cJSON_IsNull(json))
    {
        printf("%s\n", "NULL");
    } else if (cJSON_IsNumber(json))
    {
        printf("%lf\n", json->valuedouble);
    } else if (cJSON_IsString(json))
    {
        printf("%s\n", json->valuestring);
    } else if (cJSON_IsObject(json))
    {
        puts("{");
        cJSON *child;
        cJSON_ArrayForEach(child, json)
        {
            INDENT(indent + IND_DEP);
            printf("%s: ", child->string);
            print_json(child, indent + 2*IND_DEP);
        }
        INDENT(indent);
        puts("}");
    } else if (cJSON_IsArray(json))
    {
        puts("[");
        size_t count = cJSON_GetArraySize(json);
        for (size_t i = 0; i < count; i++)
        {
            INDENT(indent + IND_DEP);
            printf("[%zu]: ", i);
            print_json(cJSON_GetArrayItem(json, i), indent + IND_DEP);
        }
        INDENT(indent);
        puts("]");
    } else if (cJSON_IsInvalid(json))
    {
        printf("(invalid): %s\n", json->valuestring);
    } else {
        printf("(raw): %s\n", json->valuestring);
    }
    
}