#define MAX_SHORTENED_URL_SIZE 10
#define MAX_BIG_URL 50

struct url_dict {
  char shortened_url[MAX_SHORTENED_URL_SIZE];
  char big_url[MAX_BIG_URL];
};

typedef struct url_dict url_dict_t;
typedef struct url_dict *url_dict_ptr_t;

struct hash_table {
  int length;
  int count;
  url_dict_t **table;
};

typedef struct hash_table hash_table_t;
typedef struct hash_table *hash_table_ptr_t;

int get_total_collisions();
int get_equal();

hash_table_t *init_hash_table(int size);
void free_hash_table(hash_table_t *hash_table_members);
void insert_into_hash_table(hash_table_t *hash_table_members, char *shortened_url_key, char *big_url_value);
char *search_by_key(hash_table_t *ht, char *key);
