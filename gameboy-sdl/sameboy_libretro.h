#define FFI_LIB "sameboy_libretro.dylib"

int sprintf(char *str, const char *format, ...);
char *strdup(const char *s);

typedef void (*retro_audio_sample_t)(int16_t left, int16_t right);
typedef bool (*retro_environment_t)(unsigned cmd, void *data);
typedef void (*retro_input_poll_t)(void);
typedef int16_t (*retro_input_state_t)(unsigned port, unsigned device, unsigned index, unsigned id);
typedef void (*retro_log_printf_t)(enum retro_log_level level, const char *fmt, ...);
typedef bool (*retro_set_rumble_state_t)(unsigned port, enum retro_rumble_effect effect, uint16_t strength);
typedef void (*retro_video_refresh_t)(const void *data, unsigned width, unsigned height, size_t pitch);

bool vblank1_occurred = false, vblank2_occurred = false;

void retro_init(void);
unsigned retro_api_version(void);
bool retro_load_game(const struct retro_game_info *info);
void retro_run(void);

void retro_set_audio_sample(retro_audio_sample_t cb);

void retro_set_environment(retro_environment_t cb);

void retro_set_input_poll(retro_input_poll_t cb);
void retro_set_input_state(retro_input_state_t cb);

void retro_set_video_refresh(retro_video_refresh_t cb);

struct retro_game_info
{
   const char *path;       /* Path to game, UTF-8 encoded.
                            * Usually used as a reference.
                            * May be NULL if rom was loaded from stdin
                            * or similar. 
                            * retro_system_info::need_fullpath guaranteed 
                            * that this path is valid. */
   const void *data;       /* Memory buffer of loaded game. Will be NULL 
                            * if need_fullpath was set. */
   size_t      size;       /* Size of memory buffer. */
   const char *meta;       /* String of implementation specific meta-data. */
};

struct retro_rumble_interface
{
   retro_set_rumble_state_t set_rumble_state;
};

struct retro_variable
{
   /* Variable to query in RETRO_ENVIRONMENT_GET_VARIABLE.
    * If NULL, obtains the complete environment string if more 
    * complex parsing is necessary.
    * The environment string is formatted as key-value pairs 
    * delimited by semicolons as so:
    * "key1=value1;key2=value2;..."
    */
   const char *key;
   
   /* Value to be obtained. If key does not exist, it is set to NULL. */
   const char *value;
};