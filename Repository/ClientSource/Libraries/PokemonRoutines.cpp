/*  Pokemon Routines
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "ClientSource/CommonFramework/PushButtons.h"
#include "ClientSource/CommonPokemon/PokemonSettings.h"
#include "ClientSource/CommonPokemon/PokemonRoutines.h"
#include "ClientSource/Connection/PABotBase.h"

using namespace PokemonAutomation;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Game Entry

void resume_game_no_interact(bool tolerate_update_menu){
    resume_game_no_interact(*global_connection, tolerate_update_menu);
}
void resume_game_no_interact(PABotBase& device, bool tolerate_update_menu){
    if (tolerate_update_menu){
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
        pbf_press_dpad(device, DPAD_DOWN, 10, 10);
        pbf_press_dpad(device, DPAD_UP, 10, 10);
        pbf_press_button(device, BUTTON_A, 10, HOME_TO_GAME_DELAY);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
    }
}

void resume_game_back_out(bool tolerate_update_menu, uint16_t mash_B_time){
    resume_game_back_out(*global_connection, tolerate_update_menu, mash_B_time);
}
void resume_game_back_out(PABotBase& device, bool tolerate_update_menu, uint16_t mash_B_time){
    if (tolerate_update_menu){
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
        pbf_press_dpad(device, DPAD_DOWN, 10, 10);
        pbf_press_dpad(device, DPAD_UP, 10, 10);
        pbf_press_button(device, BUTTON_A, 10, HOME_TO_GAME_DELAY);
        pbf_mash_button(device, BUTTON_B, mash_B_time);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, HOME_TO_GAME_DELAY);
    }
}

void resume_game_front_of_den_nowatts(bool tolerate_update_menu){
    resume_game_front_of_den_nowatts(*global_connection, tolerate_update_menu);
}
void resume_game_front_of_den_nowatts(PABotBase& device, bool tolerate_update_menu){
    resume_game_back_out(device, tolerate_update_menu, 400);
}

void reset_game_from_home(bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    reset_game_from_home(*global_connection, tolerate_update_menu, user_slot, game_slot2);
}
void reset_game_from_home(PABotBase& device, bool tolerate_update_menu, uint8_t user_slot, bool game_slot2){
    pabb_reset_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.user_slot = user_slot;
    params.game_slot2 = game_slot2;
    device.issue_request<PABB_MSG_COMMAND_RESET_GAME_FROM_HOME>(params);
}

void settings_to_enter_game(bool fast){
    settings_to_enter_game(*global_connection, fast);
}
void settings_to_enter_game(PABotBase& device, bool fast){
    if (fast){
        //  100 ticks for the first press isn't enough to finish the animation.
        //  But since the HOME button has delayed effect, we start pressing the 2nd
        //  press before the animation finishes.
        pbf_press_button(device, BUTTON_HOME, 10, 90);
        pbf_press_button(device, BUTTON_HOME, 10, 0);
    }else{
        pbf_press_button(device, BUTTON_HOME, 10, 190);
        pbf_press_button(device, BUTTON_HOME, 10, 0);
    }
}
void settings_to_enter_game_den_lobby(bool tolerate_update_menu, bool fast){
    settings_to_enter_game_den_lobby(*global_connection, tolerate_update_menu, fast);
}
void settings_to_enter_game_den_lobby(PABotBase& device, bool tolerate_update_menu, bool fast){
    pabb_settings_to_enter_game_den_lobby params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_SETTINGS_TO_ENTER_GAME_DEN_LOBBY>(params);
}
void start_game_from_home(bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    start_game_from_home(*global_connection, tolerate_update_menu, game_slot, user_slot, backup_save);
}
void start_game_from_home(PABotBase& device, bool tolerate_update_menu, uint8_t game_slot, uint8_t user_slot, bool backup_save){
    pabb_start_game_from_home params;
    params.tolerate_update_menu = tolerate_update_menu;
    params.game_slot = game_slot;
    params.user_slot = user_slot;
    params.backup_save = backup_save;
    device.issue_request<PABB_MSG_COMMAND_START_GAME_FROM_HOME>(params);
}
void close_game(void){
    close_game(*global_connection);
}
void close_game(PABotBase& device){
    pabb_close_game params;
    device.issue_request<PABB_MSG_COMMAND_CLOSE_GAME>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Date Spam

void home_to_date_time(bool fast){
    home_to_date_time(*global_connection, fast);
}
void home_to_date_time(PABotBase& device, bool fast){
    pabb_home_to_date_time params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_HOME_TO_DATE_TIME>(params);
}

void roll_date_forward_1(bool fast){
    roll_date_forward_1(*global_connection, fast);
}
void roll_date_forward_1(PABotBase& device, bool fast){
    pabb_roll_date_forward_1 params;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_FORWARD_1>(params);
}

void roll_date_backward_N(uint8_t skips, bool fast){
    roll_date_backward_N(*global_connection, skips, fast);
}
void roll_date_backward_N(PABotBase& device, uint8_t skips, bool fast){
    pabb_roll_date_backward_N params;
    params.skips = skips;
    params.fast = fast;
    device.issue_request<PABB_MSG_COMMAND_ROLL_DATE_BACKWARD_N>(params);
}

#define END_YEAR    60
void home_roll_date_enter_game_autorollback(){
    home_roll_date_enter_game_autorollback(*global_connection);
}
void home_roll_date_enter_game_autorollback(PABotBase& device){
    //  This version automatically handles the 2060 roll-back.

    static uint8_t year = END_YEAR;

    if (year >= END_YEAR){
        home_roll_date_enter_game(device, true);
        year = 0;
    }else{
        home_roll_date_enter_game(device, false);
    }
    year++;
}

void home_roll_date_enter_game(bool rollback_year){
    home_roll_date_enter_game(*global_connection, rollback_year);
}
void home_roll_date_enter_game(PABotBase& device, bool rollback_year){
    pabb_home_roll_date_enter_game params;
    params.rollback_year = rollback_year;
    device.issue_request<PABB_MSG_COMMAND_HOME_ROLL_DATE_ENTER_GAME>(params);
}

void touch_date_from_home(void){
    touch_date_from_home(*global_connection);
}
void touch_date_from_home(PABotBase& device){
    pabb_touch_date_from_home params;
    device.issue_request<PABB_MSG_COMMAND_TOUCH_DATE_FROM_HOME>(params);
}

void rollback_hours_from_home(uint8_t hours){
    rollback_hours_from_home(*global_connection, hours);
}
void rollback_hours_from_home(PABotBase& device, uint8_t hours){
    pabb_rollback_hours_from_home params;
    params.hours = hours;
    device.issue_request<PABB_MSG_COMMAND_ROLLBACK_HOURS_FROM_HOME>(params);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Fast Code Entry

void enter_8digits_str(const char digits[8]){
    enter_8digits((const uint8_t*)digits);
}
void enter_8digits_str(PokemonAutomation::PABotBase& device, const char digits[8]){
    enter_8digits(device, (const uint8_t*)digits);
}
void enter_8digits(const uint8_t digits[8]){
    enter_8digits(*global_connection, digits);
}
uint8_t convert_digit(uint8_t digit){
    if (digit >= '0'){
        digit -= '0';
    }
    if (digit > 9){
        digit = 0;
    }
    return digit;
}
void enter_8digits(PokemonAutomation::PABotBase& device, const uint8_t digits[8]){
    pabb_enter_8digits params;
    params.digit01 = convert_digit(digits[0]) | (convert_digit(digits[1]) << 4);
    params.digit23 = convert_digit(digits[2]) | (convert_digit(digits[3]) << 4);
    params.digit45 = convert_digit(digits[4]) | (convert_digit(digits[5]) << 4);
    params.digit67 = convert_digit(digits[6]) | (convert_digit(digits[7]) << 4);
    device.issue_request<PABB_MSG_COMMAND_ENTER_8DIGITS>(params);

}
