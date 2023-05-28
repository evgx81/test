#include "elem.h"

Elem *elem_new(){
    Elem *elem = malloc(sizeof(Elem));
    elem->next = NULL;
    return elem;
}

void elem_free(Elem *elem){
    Elem *swap = NULL;
    do{
        swap = elem->next;
        free(elem->key);
        free(elem->value);
        free(elem);
        elem = swap;
    } while(elem->next != NULL);
}

void elem_string_parse(char **elem_string){
    int string_length = (int) strlen(*elem_string);
    int str_cursor = 0;
    char string[string_length];
    for(int cursor = 0 ; cursor < string_length ; cursor++){
        if(*(*elem_string+cursor) == '\\' && *(*elem_string+cursor+1) == '\"'){
            string[str_cursor] = '\"';
            cursor++;
        }else{
            string[str_cursor] = *(*elem_string+cursor);
        }
        str_cursor++;
    }
    string[str_cursor] = '\0';
    strcpy(*elem_string,string);
}

void elem_string_pack(char **elem_string){
    int string_length = (int) strlen(*elem_string)*2;
    int str_cursor = 0;
    char string[string_length];
    for(int cursor = 0 ; cursor < string_length ; cursor++){
        if(*(*elem_string+cursor) == '\"'){
            string[str_cursor] = '\\';
            str_cursor++;
            string[str_cursor] = '\"';
        }else{
            string[str_cursor] = *(*elem_string+cursor);
        }
        str_cursor++;
    }
    string[str_cursor] = '\0';
    strcpy(*elem_string,string);
}

void elem_parse(char *elem_pack , Elem **elem){
    char *key = malloc(sizeof(char)*strlen(elem_pack));
    char *value = malloc(sizeof(char)*strlen(elem_pack));
    int i_cursor = 0;
    int is_inner_key = 0; 
    int is_inner_value = 0;
    for(int cursor = 0 ; cursor < strlen(elem_pack) ; cursor++){
        if(is_inner_key == 0){
            if(elem_pack[cursor] == '\"' && elem_pack[cursor-1] != '\\'){
                is_inner_key = 1;
            }
        }else if(is_inner_key == 1){
            if(elem_pack[cursor] == '\"' && elem_pack[cursor-1] != '\\'){
                is_inner_key = 2;
                *(key+i_cursor) = '\0';
                i_cursor = 0;
            }else{
                *(key+i_cursor) = elem_pack[cursor];
                i_cursor++;
            }
        }else{
            if(is_inner_value == 0){
                if(elem_pack[cursor] == '\"' && elem_pack[cursor-1] != '\\'){
                    is_inner_value = 1;
                }
            }else{
                if(elem_pack[cursor] == '\"' && elem_pack[cursor-1] != '\\'){
                    *(value+i_cursor) = '\0';
                    is_inner_value = 0;
                    is_inner_key = 0;
                    i_cursor = 0;
                    realloc(key,sizeof(char)*strlen(key));
                    realloc(value,sizeof(char)*strlen(value));
                    elem_string_parse(&key);
                    elem_string_parse(&value);
                    Elem *new_elem = malloc(sizeof(Elem));
                    new_elem->key = key;
                    new_elem->value = value;
                    new_elem->next = *elem;
                    *elem = new_elem;
                    key = malloc(sizeof(char)*strlen(elem_pack));
                    value = malloc(sizeof(char)*strlen(elem_pack));
                }else{
                    *(value+i_cursor) = elem_pack[cursor];
                    i_cursor++;
                }
            }

        }
    }
    free(key);
    free(value);
}

void elem_get(struct Elem *elem , const char *key,char **value){
    Elem *swap = NULL;
    do{
        swap = elem->next;
        if(strcmp(elem->key,key) == 0){
            (*value) = malloc(sizeof(char)*strlen(elem->value));
            strcpy(*value,elem->value);
            break;
        }
        elem = swap;
    } while(elem->next != NULL);
}

Elem_Iterator* elem_iterator(struct Elem *elem){
    Elem_Iterator *elem_iterator = malloc(sizeof(Elem_Iterator));
    elem_iterator->elem = elem;
    return elem_iterator;
}

char *elem_keys_iterate(struct Elem *elem, struct Elem_Iterator **elem_iterator){
    char *return_key = (*elem_iterator)->elem->key;
    if((*elem_iterator)->elem == NULL){
        (*elem_iterator)->elem = elem;
    }
    (*elem_iterator)->elem = (*elem_iterator)->elem->next;
    return return_key;
}

Elem_Array *elem_array_new(){
    Elem_Array *elem_array = malloc(sizeof(Elem_Array));
    elem_array->next = NULL;
    return elem_array;
}

void elem_array_free(Elem_Array *elem_array){
    Elem_Array *swap = NULL;
    do{
        swap = elem_array->next;
        free(elem_array->value);
        free(elem_array);
        elem_array = swap;
    } while(elem_array->next != NULL);
}

void elem_array_pack(struct Elem_Array *elem_array , char **elem_array_pack){
    *elem_array_pack = malloc(2048*sizeof(char));
    strcat(*elem_array_pack,"}");
    Elem_Array *swap = NULL;
    int i = 0;
    do{
        elem_string_pack(&elem_array->value);
        swap = elem_array->next;
        strcat(*elem_array_pack,"\"");
        strcat(*elem_array_pack,elem_array->value);
        strcat(*elem_array_pack,"\"");
        if(elem_array->next->next != NULL){
            i = i + 1;
            if (i % 2 != 0)
                strcat(*elem_array_pack,":");
            else
                strcat(*elem_array_pack,",");
            strcat(*elem_array_pack," ");
        }
        elem_array = swap;
    } while(elem_array->next != NULL);
    strcat(*elem_array_pack,"{");
    reverse(*elem_array_pack); 
}

void elem_array_add(struct Elem_Array **elem_array , const char *value){
    Elem_Array *elem_array_item = malloc(sizeof(Elem_Array));
    char *item_value = malloc(sizeof(char)*strlen(value));
    strcpy(item_value,value);
    elem_array_item->value = item_value;
    elem_array_item->next = *elem_array;
    *elem_array = elem_array_item;
}

void swap(char *s1, char*s2)
{
	char temp;
	temp=*s1;
	 *s1=*s2;
	 *s2=temp;
	
}

int stringlength(char *s)
{
	int i;
	for(i=0;s[i];i++);
	return i;
	
}

int reverse(char *s)
{
    int a[1000],i,n,k=0,j=0,l;
     
    n=stringlength(s);
 
    for(i=0;i<n/2;i++)  
    {
    	swap(&s[i],&s[n-1-i]);
    }
 
 	for(i=0;s[i];i++)
 	{
        if(s[i]==','||s[i]==':'||s[i]=='{'||s[i]=='}')
        {
		  a[k++]=i;		   
	    }
    }
   
    a[k]=i;
       
    for(i=0;i<=k;i++)
	{
		n=a[i]-j;
		
		for(l=0;l<n/2;l++)
		{
			swap(&s[l+j],&s[a[i]-1-l]);
        }
		j=a[i]+1;
	 
	}  
	   
}

