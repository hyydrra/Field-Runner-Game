#include <iostream>
#include <math.h>
#include <algorithm>
#include "rsdl.h"
#include "FieldRunners.h"
#include "Variables.h"
#include "TowerGatling.h"
#include "ReadTextFile.h"
#include "BulletMissle.h"
#include "BulletLightning.h"
#include "BulletGoo.h"
#include "TowerMissle.h"
#include "TowerTesla.h"
#include "TowerGoo.h"
#include "SimpleRunner.h"
#include "IceRunner.h"
#include "HeavyRunner.h"
#include "BikeRunner.h"

using namespace std;



Variables variables = Variables();
string BACKGROUND_PATH = "/assets/background.png";

Window* FieldRunners::inital_window(){
    int WIDTH = variables.WIDTH;
    int HEIGHT = variables.HEIGHT;
    Window *window = new Window(WIDTH, HEIGHT);
    return window;
}

FieldRunners::FieldRunners(){
    between_wave_counter = 0;
    between_runner_counter = 0;
    between_runners_delay = 500;
    between_waye_delay = 3000;
    update_delay = variables.update_delay;
    wave_number = 0;
    start_wave_n = false;
    deplyed_runners_wave_n =0;
    player_money = 200;
    player_lives = 20;
    win = false;
    ReadTextFile txt_reader;
    enemies_list = txt_reader.read(enemy_path);
    all_houses_in_path = all_hoouse_of_path();
}


void FieldRunners::run_game() {
    Window *window = inital_window();
    long time_steps = 0;
    bool GAME_RUNNING = true;
    bool GAME_RUNNING1 = true;
    bool lclicked = false;
    Point mousePosition;
    window->play_music(variables.PROJECT_PATH + "/assets/extra_selected/musics/Grasslands.mp3");

    start_page(window,GAME_RUNNING);

    while (GAME_RUNNING && GAME_RUNNING1) {
        time_steps++;
        load_background(window);
        show_heart_gold(window);

        Event event = get_event(window);
        GAME_RUNNING = prossec_event(event, lclicked, mousePosition);

        prossec_towers_bullets(window);
        prossec_enemies(window, time_steps);
        delay(update_delay);
        GAME_RUNNING1 = check_win_loss();
    }
    result_page(window,GAME_RUNNING,GAME_RUNNING1);
}




void FieldRunners::show_heart_gold(Window* window){
    window->show_text("Hearts: "+to_string(player_lives)+ "     Golds: "+ to_string(player_money),
                      Point(570, 60), BLACK,
                      variables.PROJECT_PATH + "/assets/OpenSans.ttf", 20);

    TowerGatling *t1 = new TowerGatling(0, 0);
    window->show_text("g : Gattling ==> Build cost ="+ to_string(t1->get_build_cost())+", Upgrade cost =" + to_string(t1->get_upgrade_cost()),
                      Point(0, window->get_height()-200), WHITE,
                      variables.PROJECT_PATH + "/assets/OpenSans.ttf", 15);
    delete t1;
    TowerMissle *t2 = new TowerMissle(0, 0);
    window->show_text("m : Missle ==> Build cost ="+ to_string(t2->get_build_cost())+", Upgrade cost =" + to_string(t2->get_upgrade_cost()),
                      Point(0, window->get_height()-175), WHITE,
                      variables.PROJECT_PATH + "/assets/OpenSans.ttf", 15);
    delete t2;
    TowerGoo *t3 = new TowerGoo(0, 0);
    window->show_text("y : Goo ==> Build cost ="+ to_string(t3->get_build_cost())+", Upgrade cost =" + to_string(t3->get_upgrade_cost()),
                      Point(0, window->get_height()-150), WHITE,
                      variables.PROJECT_PATH + "/assets/OpenSans.ttf", 15);
    delete t3;
    TowerTesla *t4 = new TowerTesla(0, 0);
    window->show_text("t : Tesla ==> Build cost ="+ to_string(t4->get_build_cost())+", Upgrade cost =" + to_string(t4->get_upgrade_cost()),
                      Point(0, window->get_height()-125), WHITE,
                      variables.PROJECT_PATH + "/assets/OpenSans.ttf", 15);
    delete t4;
}

void FieldRunners::result_page(Window* window, bool game_running, bool game_running1) {
    if (game_running1 == 0) {
        delay(3000);
        while (true) {
            show_win_loss_massage(window);
            window->show_text("press any key to exit the game", Point(370, 800), WHITE,
                              variables.PROJECT_PATH + "/assets/OpenSans.ttf", 40);
            window->update_screen();
            if (get_event(window).get_type() == Event::KEY_RELEASE) { break; }
            if (get_event(window).get_type() == Event::QUIT) { break; }
        }
    }
}

void FieldRunners::start_page(Window* window, bool& start_game){
    while (true) {
        window->draw_img(variables.PROJECT_PATH + "/assets/extra_selected/stuff/starpage.jpg") ;
        window->show_text("press any key to start the game",Point(370 ,800),WHITE,variables.PROJECT_PATH + "/assets/OpenSans.ttf",40);
        window->update_screen();
        if(get_event(window).get_type() == Event::KEY_RELEASE){ break;}
        if(get_event(window).get_type() == Event::QUIT){
            start_game = false;
            break;
        }
    }
}

void FieldRunners::show_win_loss_massage(Window* window){
    if(win){
        window->draw_img(variables.PROJECT_PATH+"/assets/extra_selected/stuff/win.jpg");
    }
    else{
        window->draw_img(variables.PROJECT_PATH+"/assets/extra_selected/stuff/loss.jpg");
    }
    window->update_screen();
}

void FieldRunners::prossec_towers_bullets(Window* window){
    add_enemy_to_map();
    assign_targets_to_towers();

    for(int i=0; i<player_towers.size(); i++){
        bool if_fired = player_towers[i]->shot_target(update_delay);
        if (if_fired){
            fire_sound_effects(window,player_towers[i]);
            add_bullet(player_towers[i]);
        }
        player_towers[i]->draw(window);
    }
    for(int i=0; i<bullets.size(); i++){
        bullets[i]->update_position(update_delay);
        bullets[i]->draw(window);
    }
    update_bullets();
}

void FieldRunners::prossec_enemies(Window* window, int time_steps){
    update_live_enemies();
    for(int i=0; i<live_enemies.size(); i++){
        live_enemies[i]->update_position(time_steps);
        live_enemies[i]->draw(window);
    }
    window->update_screen();
}

bool FieldRunners::check_win_loss(){
    if (player_lives <= 0){
        win = false;
        return false;
    }
    else if (wave_number >= enemies_list.size() && live_enemies.size() == 0){
        win = true;
        return false;
    }
    return true;
}

Event FieldRunners::get_event(Window* window){
    while(window->has_pending_event()) {return window->poll_for_event();}
}

void FieldRunners::load_background(Window *window) {
    string PROJECT_PATH = variables.PROJECT_PATH;
    string path = PROJECT_PATH + BACKGROUND_PATH;
    window->draw_img(path);
    for(int i=0; i<all_houses_in_path.size(); i++){
        window->draw_img(variables.PROJECT_PATH +"/assets/extra_selected/stuff/brick-pattern-background-construction.jpg",
                Rectangle(home_number_to_pixel(all_houses_in_path[i]).x -variables.lengh_home/2,
                        home_number_to_pixel(all_houses_in_path[i]).y -variables.lengh_home/2,variables.lengh_home,variables.lengh_home));
    }
}

bool FieldRunners::prossec_event(Event event, bool& lclicked, Point& mousePosition){
    switch (event.get_type()) {
        case Event::EventType::QUIT:
            return 0;
        case Event::EventType::LCLICK: {
            lclicked = true;
            mousePosition = event.get_mouse_position();
        }
        case Event::EventType::KEY_PRESS:
            if (lclicked) { key_press_handler(event, lclicked, mousePosition);}
    }
    return 1;
}

void FieldRunners::key_press_handler(Event event, bool& lclicked, Point mousePosition){
    char pressed_key = event.get_pressed_key();
    if(check_if_house_in_map(mousePosition)){
        Point center_posion = home_number_to_pixel(nearest_house_center(mousePosition));
        if (check_if_house_is_empty(nearest_house_center(mousePosition))){
            add_tower(center_posion, lclicked, pressed_key);
        }
        else{
            upgrade_tower(nearest_house_center(mousePosition), lclicked, pressed_key);
        }
    }
}

void FieldRunners::add_tower(Point center_posion, bool& lclicked, char pressed_key) {
    if (pressed_key == 'g') {
        TowerGatling *gatteling = new TowerGatling(center_posion.x, center_posion.y);
        if (gatteling->get_build_cost() <= player_money) {
            player_towers.push_back(gatteling);
            lclicked = false;
            player_money = player_money - gatteling->get_build_cost();
        }
    }
    else if (pressed_key == 'm') {
        TowerMissle *missile = new TowerMissle(center_posion.x, center_posion.y);
        if (missile->get_build_cost() <= player_money) {
            player_towers.push_back(missile);
            lclicked = false;
            player_money = player_money - missile->get_build_cost();
        }
    } 
    else if (pressed_key == 't') {
        TowerTesla *tesla = new TowerTesla(center_posion.x, center_posion.y);
        if (tesla->get_build_cost() <= player_money) {
            player_towers.push_back(tesla);
            lclicked = false;
            player_money = player_money - tesla->get_build_cost();
        }
    } 
    else if (pressed_key == 'l') {
        TowerGoo *goo = new TowerGoo(center_posion.x, center_posion.y);
        if (goo->get_build_cost() <= player_money) {
            player_towers.push_back(goo);
            lclicked = false;
            player_money = player_money - goo->get_build_cost();
        }
    }
}

void FieldRunners::add_enemy_to_map() {
    if (live_enemies.size() == 0) { between_wave_counter++; }
    if ((between_wave_counter > between_waye_delay / update_delay) && wave_number < enemies_list.size() ) {
        start_wave_n = true;
        between_wave_counter = 0;
    }
    if (start_wave_n) {
        between_runner_counter++;
        if (between_runner_counter % int(between_runners_delay / update_delay) == 0) {
            vector<int> wave_n_runners_list = enemies_list[wave_number];
            if (deplyed_runners_wave_n < wave_n_runners_list.size()) {
                runner_type_handler(wave_n_runners_list[deplyed_runners_wave_n]);
                deplyed_runners_wave_n++;
            }
            else{
                start_wave_n = false;
                wave_number++;
                deplyed_runners_wave_n =0;
            }
        }
    }
}

void FieldRunners::runner_type_handler(int type) {
    if (type == 1) {
        SimpleRunner *runner = new SimpleRunner(wave_number, enemy_path);
        live_enemies.push_back(runner);
    }
    else if (type == 2) {
        IceRunner *runner = new IceRunner(wave_number, enemy_path);
        live_enemies.push_back(runner);
    }
    else if (type == 3) {
        HeavyRunner *runner = new HeavyRunner(wave_number, enemy_path);
        live_enemies.push_back(runner);
    }
    else if (type == 4) {
        BikeRunner *runner = new BikeRunner(wave_number, enemy_path);
        live_enemies.push_back(runner);
    }
}

void FieldRunners::assign_targets_to_towers(){
    if (live_enemies.size()>0){
        vector<Enemy*> targetable_enemies;
        for(int i=0; i<player_towers.size(); i++){
            targetable_enemies = get_targetable_enemies(player_towers[i]);
            if (targetable_enemies.size()>0){
                float min_target_dis = distance_between_two_point(live_enemies[nearest_enemy_index(i,targetable_enemies)]->get_location(),player_towers[i]->get_location());
                player_towers[i]->set_target(live_enemies[nearest_enemy_index(i,targetable_enemies)],min_target_dis);
            }
        }
    }
}

float FieldRunners::distance_between_two_point(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int FieldRunners::nearest_enemy_index(int tower_index, vector<Enemy*> targetable_enemies){
    Point tower_position = player_towers[tower_index]->get_location();
    int min_distance = 10*(variables.HEIGHT + variables.WIDTH);
    int min_index;
    for (int i=0; i<targetable_enemies.size(); i++){
        if (distance_between_two_point(tower_position, targetable_enemies[i]->get_location()) < min_distance){
            min_distance = distance_between_two_point(tower_position, targetable_enemies[i]->get_location());
            min_index = i;
        }
    }
    return min_index;
}

void FieldRunners::update_live_enemies(){
    vector<int> new_deaths;
    for (int i=0; i<live_enemies.size(); i++){
        if (live_enemies[i]->get_remaining_health() <= 0){
            player_money = player_money + live_enemies[i]->get_killing_prize();
            new_deaths.push_back(i);
        }
        else if(live_enemies[i]->reached_end()){
            player_lives = player_lives - live_enemies[i]->get_damage();
            new_deaths.push_back(i);
        }
    }
    live_enemies = remove_multiple_elemts_from_enemy_vector(live_enemies, new_deaths);
}

vector<Enemy*> FieldRunners::remove_multiple_elemts_from_enemy_vector(vector<Enemy*> vect, vector<int> removelist){
    std::sort(removelist.begin(), removelist.end());
    for (auto i = removelist.rbegin(); i != removelist.rend(); ++ i)
    {
        vect.erase(vect.begin() + *i);
    }
    return vect;
}

vector<Bullet*> FieldRunners::remove_multiple_elemts_from_bullet_vector(vector<Bullet*> vect, vector<int> removelist){
    std::sort(removelist.begin(), removelist.end());
    for (auto i = removelist.rbegin(); i != removelist.rend(); ++ i)
    {
        vect.erase(vect.begin() + *i);
    }
    return vect;
}

void FieldRunners::update_bullets(){
    vector<int> new_deaths;
    for (int i=0; i<bullets.size(); i++){
        if (bullets[i]->get_reached()){
            new_deaths.push_back(i);
            Towers* t = bullets[i]->get_tower();
            t->enter_damage(bullets[i]->get_target(), live_enemies);
        }
    }
    bullets = remove_multiple_elemts_from_bullet_vector(bullets, new_deaths);
}

void FieldRunners::add_bullet(Towers* tower){
    if (tower->get_name() == "goo"){
        BulletGoo *bullet = new BulletGoo(tower);
        bullets.push_back(bullet);
    }
    if (tower->get_name() == "tesla"){
        BulletLightning *bullet = new BulletLightning(tower);
        bullets.push_back(bullet);
    }
    if (tower->get_name() == "missile"){
        BulletMissle *bullet = new BulletMissle(tower);
        bullets.push_back(bullet);
    }
}

Point FieldRunners::home_number_to_pixel(Point row_col) {
    int x = variables.top_left_home_center.x + (row_col.x * variables.lengh_home);
    int y = variables.top_left_home_center.y + (row_col.y * variables.lengh_home);
    return Point(x, y);
}

Point FieldRunners::nearest_house_center(Point point){
    int x = floor(float(point.x - variables.top_left_home_center.x + variables.lengh_home/2) / float(variables.lengh_home));
    int y = floor(float(point.y - variables.top_left_home_center.y + variables.lengh_home/2) / float(variables.lengh_home));
    return Point(x,y);
}

bool FieldRunners::check_if_house_is_empty(Point point){
    vector<Point> all_path = all_houses_in_path;
    for (int i=0; i<all_path.size(); i++){
        if (point.x == all_path[i].x && point.y == all_path[i].y){return 0;}
    }
    for (int i=0; i<player_towers.size(); i++){
        Point tower_loc = nearest_house_center(player_towers[i]->get_location());
        if (point.x == tower_loc.x && point.y == tower_loc.y){return 0;}
    }
    return 1;
}

vector<Point> FieldRunners::all_hoouse_of_path(){
    vector<Point> all_houses;
    for (int i=0; i<enemy_path.size()-1; i++) {
        int dx =  enemy_path[i+1].x - enemy_path[i].x;
        int dy = enemy_path[i+1].y - enemy_path[i].y;
        int num_home_between_two_destination = abs(dx) + abs(dy);
        all_houses.push_back(enemy_path[i]);
        for( int j=0; j<num_home_between_two_destination; j++) {
            all_houses.push_back(Point(enemy_path[i].x + sign(dx)*(j+1), enemy_path[i].y + sign(dy)*(j+1)));
        }
    }
    all_houses.push_back(enemy_path[enemy_path.size()-1]);
    return all_houses;
}

int FieldRunners::sign(int x){
    if (x > 0) {return 1;}
    if (x < 0) {return -1;}
    return 0;
}

bool FieldRunners::check_if_house_in_map(Point point) {
    int minx = variables.top_left_home_center.x - variables.lengh_home/2;
    int miny = variables.top_left_home_center.y - variables.lengh_home/2;
    int maxx = variables.top_left_home_center.x + ((variables.num_column-1) * variables.lengh_home) + variables.lengh_home/2 ;
    int maxy = variables.top_left_home_center.y + ((variables.num_rows-1) * variables.lengh_home) + variables.lengh_home/2 ;
    if (point.x < minx || point.x > maxx) { return 0; }
    if (point.y < miny || point.y > maxy) { return 0; }
    return 1;
}

bool FieldRunners::upgrade_tower(Point center_posion, bool& lclicked, char pressed_key){
    bool upgraded = false;
    if (pressed_key == 'u'){
        for (int i=0; i<player_towers.size(); i++){
            Point tower_loc = nearest_house_center(player_towers[i]->get_location());
            if (center_posion.x == tower_loc.x && center_posion.y == tower_loc.y){
                if(player_towers[i]->get_build_cost() < player_money){
                    player_money = player_money - player_towers[i]->get_build_cost();
                    upgraded = player_towers[i]->upgrade();
                }
            }
        }
        lclicked = false;
    }
    return upgraded;
}

vector<Enemy*> FieldRunners::get_targetable_enemies(Towers* tower){
    vector<Enemy*> targetable_enemies;
    if (tower->get_name() == "goo"){
        for (int i=0; i<live_enemies.size(); i++){
            if (live_enemies[i]->get_name() != "IceRunner"){ targetable_enemies.push_back(live_enemies[i]);}
        }
    }
    else if (tower->get_name() == "gatling"){
        for (int i=0; i<live_enemies.size(); i++){
            if (live_enemies[i]->get_name() != "IceRunner"){ targetable_enemies.push_back(live_enemies[i]);}
        }
    }
    else { targetable_enemies = live_enemies;}
    return targetable_enemies;
}

void FieldRunners::fire_sound_effects(Window* window, Towers* tower){
    if (tower->get_name() == "gatling"){
        window->play_sound_effect(variables.PROJECT_PATH+"/assets/extra_selected/musics/Automatic Machine Gun-SoundBible.com-253461580.mp3");
    }
    if (tower->get_name() == "tesla"){
        window->play_sound_effect(variables.PROJECT_PATH+"/assets/extra_selected/musics/tesla_zap_01.ogg");
    }
    if (tower->get_name() == "missile"){
        window->play_sound_effect(variables.PROJECT_PATH+"/assets/extra_selected/musics/missile.mp3");
    }
}