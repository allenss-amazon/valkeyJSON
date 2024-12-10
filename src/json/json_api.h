/**
 * JSON C API
 */
#ifndef VALKEYJSONMODULE_JSON_API_H_
#define VALKEYJSONMODULE_JSON_API_H_

#include <stdlib.h>

typedef struct ValkeyModuleCtx ValkeyModuleCtx;
typedef struct ValkeyModuleKey ValkeyModuleKey;
typedef struct ValkeyModuleString ValkeyModuleString;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Is it a JSON key?
 */
int is_json_key(ValkeyModuleCtx *ctx, ValkeyModuleKey *key);

/**
 * Another version of is_json_key, given key name as ValkeyModuleString
 */
int is_json_key2(ValkeyModuleCtx *ctx, ValkeyModuleString *keystr);

/**
 * Get the type of the JSON value at the path. The path is expected to point to a single value.
 * If multiple values match the path, only the type of the first one is returned.
 *
 * @type output param, JSON type. The caller is responsible for freeing the memory.
 * @len output param, length of JSON type.
 * @return 0 - success, 1 - error
 */
int get_json_value_type(ValkeyModuleCtx *ctx, const char *keyname, const size_t key_len, const char *path,
                        char **type, size_t *len);

/**
 * Get serialized JSON value at the path. The path is expected to point to a single value.
 * If multiple values match the path, only the first one is returned.
 *
 * @value output param, serialized JSON string. The caller is responsible for freeing the memory.
 * @len output param, length of JSON string.
 * @return 0 - success, 1 - error
 */
int get_json_value(ValkeyModuleCtx *ctx, const char *keyname, const size_t key_len, const char *path,
                   char **value, size_t *len);

/**
 * Get serialized JSON values and JSON types at multiple paths. Each path is expected to point to a single value.
 * If multiple values match the path, only the first one is returned.
 *  
 * @values      Output param, array of JSON strings.
 *              The caller is responsible for freeing the memory: the array '*values' as well as all the strings '(*values)[i]'.
 * @lengths     Output param, array of lengths of each JSON string.
 *              The caller is responsible for freeing the memory: the array '*lengths'.
 * @types       Output param, array of types as strings. The caller is responsible for freeing the memory.
 *              The caller is responsible for freeing the memory: the array '*types' as well as all the strings '(*types)[i]'.
 * @type_lengths        Output param, array of lengths of each type string.
 *                      The caller is responsible for freeing the memory: the array '*type_lengths'.
 * @return 0 - success, 1 - error
 */
int get_json_values_and_types(ValkeyModuleCtx *ctx, const char *keyname, const size_t key_len, const char **paths,
                    const int num_paths, char ***values, size_t **lengths, char ***types, size_t **type_lengths);

/* *
 * Get a reference counted pointer to a vector iff:
 * * The first value it hits is an all number array with the right number (dimensionality) of all number elements and it successfully converts it.
 * * The first value it hits is a vector of the correct dimensionality already.
 * Otherwise, it returns `nullptr` on failure.
 * Note that when calling this function, we use RedisModule_AMZ_SharedMemory_Clone() to make increment the reference counting to this memory.
 * So if a caller successfully gets a non-null pointer, at some point, that caller must call RedisModule_AMZ_SharedMemory_Drop() on the memory.
 * @vector output param, the JSON vector value is stored in it.
 * @ return 0 - success, -1 - error
 */
int get_json_vector_f32(ValkeyModuleCtx *ctx, const char *keyname, const size_t key_len, const char *path,
        const size_t dimensionality, float **vector);

#ifdef __cplusplus
}
#endif

#endif
