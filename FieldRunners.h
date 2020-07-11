#ifndef FIELDRUNNERS_H
#define FIELDRUNNERS_H


#include "rsdl.h"
#include "Towers.h"
#include "Enemy.h"
#include "Bullet.h"
class FieldRunners {

public:
    FieldRunners();
    void run_game();

private:
    std::vector<Towers*> player_towers;
    std::vector<Enemy*> live_enemies;
    std::vector<Bullet*> bullets;
    int between_wave_counter;
    int between_runner_counter;
    float between_waye_delay;
    float between_runners_delay;
    float update_delay;
    bool start_wave_n;
    int deplyed_runners_wave_n;
    int wave_number;
    int player_lives;
    int player_money;
    bool win;

    std::vector<Point> enemy_path;
    std::vector<Point> all_houses_in_path;
    std::vector<std::vector<int>> enemies_list;
    Event get_event(Window *window);
    void load_background(Window *window);
    bool prossec_event(Event event, bool &lclicked, Point &mousePosition);
    void key_press_handler(Event event, bool &lclicked, Point mousePosition);
    Window *inital_window();
    void add_enemy_to_map();
    void runner_type_handler(int type);
    void assign_targets_to_towers();
    float distance_between_two_point(Point p1, Point p2);
    std::vector<Enemy *> remove_multiple_elemts_from_enemy_vector(std::vector<Enemy *> vect, std::vector<int> removelist);
    void update_bullets();
    std::vector<Bullet *> remove_multiple_elemts_from_bullet_vector(std::vector<Bullet *> vect, std::vector<int> removelist);
    Point nearest_house_center(Point point);
    Point home_number_to_pixel(Point row_col);
    bool check_if_house_is_empty(Point point);
    std::vector<Point> all_hoouse_of_path();
    int sign(int x);
    bool check_if_house_in_map(Point point);
    void add_tower(Point center_posion, bool &lclicked, char pressed_key);
    bool upgrade_tower(Point center_posion, bool &lclicked, char pressed_key);
    int nearest_enemy_index(int tower_index, std::vector<Enemy *> targetable_enemies);
    std::vector<Enemy *> get_targetable_enemies(Towers *tower);
    void update_live_enemies();
    void fire_sound_effects(Window *window, Towers *tower);
    void add_bullet(Towers *tower);
    void prossec_towers_bullets(Window *window);
    void prossec_enemies(Window *window, int time_steps);
    bool check_win_loss();
    void show_win_loss_massage(Window *window);
    void start_page(Window *window, bool &start_game);
    void result_page(Window *window, bool game_running, bool game_running1);
    void show_heart_gold(Window *window);
};


#endif
