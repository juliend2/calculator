// Include gtk4
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_BUTTONS 10

typedef struct {
    char *left_operand;
    char *operator;
    char *right_operand;
} Operation;

Operation operation = { NULL, NULL, NULL };

int left_operand;

int row_for_button_index(int index) {
    if (index < 3) {
        return 0;
    } else if (index < 6) {
        return 1;
    } else if (index < 9) {
        return 2;
    } else {
        return 3;
    }
}

void assign_left_operand(int operand) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", operand);
    // Allocate memory and copy the string to left_operand:
    operation.left_operand = malloc((strlen(buffer) + 1) * sizeof(char));
    if (operation.left_operand == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(operation.left_operand, buffer);
}

bool is_integer(char value) {
    return value >= '0' && value <= '9';
}

void append_char(char *str, char c, size_t max_len) {
    size_t len = strlen(str);
    if (len + 1 < max_len) {
        str[len] = c;
        str[len + 1] = '\0';
    } else {
        fprintf(stderr, "Buffer overflow prevented\n");
    }
}

static void button_click(GtkButton *button, gpointer passed_label) {
    GtkWidget *label = GTK_WIDGET(passed_label);
    const char *name = gtk_button_get_label(button);
    // char result_str[20];
    // int result = left_operand + operand;
    
    if (is_integer(*name)) {
        if (operation.left_operand == NULL) {
            int operand = atoi(name);
            assign_left_operand(operand);
        } else {
            // operation.left_operand 
            append_char(operation.left_operand, name[0], sizeof(char *));
        }
    }
    // snprintf(result_str, sizeof(result_str), "%d", result);
    // gtk_label_set_text(GTK_LABEL(label), result_str);
    gtk_label_set_text(GTK_LABEL(label), operation.left_operand);
}

// static void calculate(GtkButton *button, gpointer passed_label) {
//     GtkWidget *label = GTK_WIDGET(passed_label);
//     const char *name = gtk_button_get_label(button);
//     int operand = atoi(name);
//     char result_str[20];
//     int result = left_operand + operand;
//     snprintf(result_str, sizeof(result_str), "%d", result);
//     gtk_label_set_text(GTK_LABEL(label), result_str);
// }

static void on_activate(GtkApplication *app) {
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);

    GtkWidget *buttons[NUM_BUTTONS];
    const char *button_labels[NUM_BUTTONS] = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "0"
    };

    GtkWidget *label = gtk_label_new("_");
    GtkWidget *grid = gtk_grid_new();

    int column = 0;
    int row = 0;
    for (int i = 0; i < NUM_BUTTONS; i++) {
        buttons[i] = gtk_button_new_with_label(button_labels[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_click), label);
        row = row_for_button_index(i);
        column = i % 3;
        gtk_grid_attach(GTK_GRID(grid), buttons[i], column, row, 1, 1);
    }

    gtk_grid_attach(GTK_GRID(grid), label, 1, 3, 1, 1);

    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char *argv[]) {
    int status;
    left_operand = 8;
    // Create a new application
    GtkApplication *app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

