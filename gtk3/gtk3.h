#define FFI_LIB "/usr/local/Cellar/gtk+3/3.24.11/lib/libgtk-3.dylib"

typedef char   gchar;
typedef short  gshort;
typedef long   glong;
typedef int    gint;
typedef gint   gboolean;

typedef unsigned char   guchar;
typedef unsigned short  gushort;
typedef unsigned long   gulong;
typedef unsigned int    guint;

typedef float   gfloat;
typedef double  gdouble;

typedef unsigned long gsize;

typedef gsize GType;

typedef struct _GtkContainer GtkContainer;

struct _GTypeClass
{
  GType g_type;
};

typedef struct _GTypeClass GTypeClass;

struct _GTypeInstance
{
  GTypeClass *g_class;
};

typedef struct _GTypeInstance GTypeInstance;
typedef struct _GData GData;

struct  _GObject
{
  GTypeInstance  g_type_instance;
  volatile guint ref_count;
  GData         *qdata;
};

typedef struct _GObject GInitiallyUnowned;
typedef struct _GtkWidget GtkWidget;
typedef struct _GtkWidgetPrivate GtkWidgetPrivate;

typedef enum
{
  GTK_WINDOW_TOPLEVEL,
  GTK_WINDOW_POPUP
} GtkWindowType;

struct _GtkWidget
{
  GInitiallyUnowned parent_instance;
  GtkWidgetPrivate *priv;
};

void gtk_init(int *argc, char ***argv);
void gtk_main(void);
GtkWidget* gtk_button_new_with_label(const gchar *label);
// GtkContainer is the correct, but GtkWidget works :-)
void gtk_container_add(GtkWidget *container, GtkWidget *widget);
void gtk_container_set_border_width(GtkWidget *container, guint border_width);
GtkWidget* gtk_window_new(GtkWindowType type);
// GtkWindow is the correct, but GtkWidget works :-)
void gtk_window_set_title(GtkWidget *window, const gchar *title);
void gtk_widget_show_all(GtkWidget *widget);
