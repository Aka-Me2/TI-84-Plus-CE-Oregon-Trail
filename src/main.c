#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>
#include <ti/tokens.h>
#include <sys/timers.h>
#include <math.h>
#include <string.h>

int oxen_spending, 
food_spending = -1, 
ammo_spending = -1, 
clothing_spending = -1, 
misc_spending = -1,
cash_left, 
total_mileage, 
current_turn = 0,
player_shooting_skill;

bool illnes_flag = false, injury_flag = false,
south_pass_flag = false, fort_option_flag = false,
blizzard_flag = false, blue_mountain_flag = false;

void initial_game_setup();
void get_player_shooting_skill();
void initial_purchases();
void main_loop();

int main()
{
    os_ClrHome();

    initial_game_setup();
    get_player_shooting_skill();
    initial_purchases();
    main_loop();

    return 0;
}

int get_int_input()
{
    int int_input = 0;
    bool break_loop = false;

    while (break_loop == false)
    {
        int place  = 0;

        switch(os_GetKey())
        {
        case k_0:
            int_input *= 10;
            place += 1;
            break;
        case k_1:
            int_input += 1*10^place;
            place += 1;
            break;
        case k_2:
            int_input += 2*10^place;
            place += 1;
            break;
        case k_3:
            int_input += 3*10^place;
            place += 1;
            break;
        case k_4:
            int_input += 4*10^place;
            place += 1;
            break;
        case k_5:
            int_input += 5*10^place;
            place += 1;
            break;
        case k_6:
            int_input += 6*10^place;
            place += 1;
            break;
        case k_7:
            int_input += 7*10^place;
            place += 1;
            break;
        case k_8:
            int_input += 8*10^place;
            place += 1;
            break;
        case k_9:
            int_input += 9*10^place;
            place += 1;
            break;
        case k_Enter:
            break_loop = true;
            break;
        }
    }
    return int_input;
}

void initial_game_setup()
{
    char ans[4];
    os_GetStringInput("DO YOU NEED INSTRUCTIONS (YES/NO)", ans, 4);
    if(strcmp(ans, "YES") == 0)
    {
        os_PutStrFull("THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM");
        os_NewLine();
        os_PutStrFull("INDEPENDENCES, MISSOURI TO OREGON CITY, OREGON IN 1847");
        os_NewLine();
        os_PutStrFull("YOUR FAMILY OF FIVE WILL COVER THE 2040 MILE OREGON TRAIL");
        os_NewLine();
        os_PutStrFull("IN 5-6 MONTHS --- IF YOU MAKE IT ALIVE.");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("YOU HAD SAVED $900 TO SPEND FOR THE TRIP, AND YOU'VE JUST");
        os_NewLine();
        os_PutStrFull("   PAID $200 FOR A WAGON.");
        os_NewLine();
        os_PutStrFull("YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE");
        os_NewLine();
        os_PutStrFull("   FOLLOWING ITEMS:");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("     OXEN - YOU CAN SPEND $200-$300 ON YOUR TEAM");
        os_NewLine();
        os_PutStrFull("            THE MORE YOU SPEND, THE FASTER YOU'LL GO");
        os_NewLine();
        os_PutStrFull("               BECAUSE YOU'LL HAVE BETTER ANIMALS");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("     FOOD - THE MORE YOU HAVE, THE LESS CHANCE THERE");
        os_NewLine();
        os_PutStrFull("               IS OF GETTING SICK");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("     AMMUNITION - $1 BUYS A BELT OF 50 BULLETS");
        os_NewLine();
        os_PutStrFull("            YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS");
        os_NewLine();
        os_PutStrFull("               AND BANDITS, AND FOR HUNTING FOOD");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("     CLOTHING - THIS IS ESPECIALLY IMPORTANT FOR THE COLD");
        os_NewLine();
        os_PutStrFull("               WEATHER YOU WILL ENCOUNTER WHEN CROSSING");
        os_NewLine();
        os_PutStrFull("               THE MOUNTAINS");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("     MISCELLANEOUS SUPPLIES - THIS INCLUDES MEDICINE AND");
        os_NewLine();
        os_PutStrFull("              OTHER THINGS YOU WILL NEED FOR SICKNESS");
        os_NewLine();
        os_PutStrFull("              AND EMERGENCY REPAIRS");
        os_NewLine();
        os_NewLine();
        os_NewLine();
        os_PutStrFull("YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP -");
        os_NewLine();
        os_PutStrFull("OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG");
        os_NewLine();
        os_PutStrFull("THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT");
        os_NewLine();
        os_PutStrFull("THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET");
        os_NewLine();
        os_PutStrFull("MORE FOOD.");
        os_NewLine();
        os_PutStrFull("WHENEVER YOU HAVE TO USE YOUR TRUSTY RIFLE ALONG THE WAY,");
        os_NewLine();
        os_PutStrFull("YOU WILL BE TOLD TO TYPE IN THAT WORD (ONE THAT SOUNDS LIKE A");
        os_NewLine();
        os_PutStrFull("GUN SHOT). THE FASTER YOU TYPE IN THAT WORD AND HIT THE");
        os_NewLine();
        os_PutStrFull("""RETURN"" KEY, THE BETTER LUCK YOU'LL HAVE WITH YOUR GUN.");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("AT EACH TURN, ALL ITEMS ARE SHOWN IN DOLLAR AMOUNTS");
        os_NewLine();
        os_PutStrFull("EXCEPT BULLETS");
        os_NewLine();
        os_PutStrFull("WHEN ASKED TO ENTER MONEY AMOUNTS, DON'T USE A ""$"".");
        os_NewLine();
        os_NewLine();
        os_PutStrFull("GOOD LUCK!!!");
        os_NewLine();
        os_NewLine();
        os_NewLine();
    }
}

void get_player_shooting_skill()
{
    os_PutStrFull("HOW GOOD A SHOT ARE YOU WITH YOUR RIFLE?");
    os_NewLine();
    os_PutStrFull("  (1) ACE MARKSMAN,  (2) GOOD SHOT,  (3) FAIR TO MIDDLIN'");
    os_NewLine();
    os_PutStrFull("         (4) NEED MORE PRACTICE,  (5) SHAKY KNEES");
    os_NewLine();
    os_PutStrFull("ENTER ONE OF THE ABOVE -- THE BETTER YOU CLAIM YOU ARE, THE");
    os_NewLine();
    os_PutStrFull("FASTER YOU'LL HAVE TO BE WITH YOUR GUN TO BE SUCCESSFUL.");
    os_NewLine();
    os_PutStrFull("?");
    player_shooting_skill = get_int_input();
}

void initial_purchases()
{
    while((700 - oxen_spending - food_spending - ammo_spending - clothing_spending - misc_spending) < 0)
    {
        os_NewLine();
        os_NewLine();
        os_NewLine();
        os_PutStrFull("HOW MUCH DO YOU WANT TO SPEND ON YOUR OXEN TEAM");
        while(oxen_spending < 200 && oxen_spending > 300)
        {
            oxen_spending = get_int_input();
            if(oxen_spending < 200)
            {
                os_NewLine();
                os_PutStrFull("NOT ENOUGH");
    
            }else if(oxen_spending > 300)
            {
                os_NewLine();
                os_PutStrFull("TOO MUCH");
            }
        }
    
        os_NewLine();
        os_PutStrFull("HOW MUCH DO YOU WANT TO SPEND ON FOOD");
        while(food_spending < 0)
        {
            food_spending = get_int_input();
            if(food_spending < 0)
            {
                os_NewLine();
                os_PutStrFull("IMPOSSIBLE");
            }
        }
        
        os_NewLine();
        os_PutStrFull("HOW MUCH DO YOU WANT TO SPEND ON AMMUNITION");
        while(ammo_spending < 0)
        {
            ammo_spending = get_int_input();
            if(ammo_spending < 0)
            {
                os_NewLine();
                os_PutStrFull("IMPOSSIBLE");
            }
        }
    
        os_NewLine();
        os_PutStrFull("HOW MUCH DO YOU WANT TO SPEND ON CLOTHING");
        while(clothing_spending < 0)
        {
            clothing_spending = get_int_input();
            if(clothing_spending < 0)
            {
                os_NewLine();
                os_PutStrFull("IMPOSSIBLE");
            }
        }
    
        os_NewLine();
        os_PutStrFull("HOW MUCH DO YOU WANT TO SPEND ON MISCELLANEOUS SUPPLIES");
        while(misc_spending < 0)
        {
            misc_spending = get_int_input();
            if(misc_spending < 0)
            {
                os_NewLine();
                os_PutStrFull("IMPOSSIBLE");
            }
        }

        if((700 - oxen_spending - food_spending - ammo_spending - clothing_spending - misc_spending) < 0)
        {
            os_NewLine();
            os_PutStrFull("YOU OVERSPENT--YOU ONLY HAD $700 TO SPEND. BUY AGAIN");
        }
    }

    // Print how many dollars are left
    os_NewLine();
    os_NewLine();
    os_PutStrFull("MONDAY MARCH 29 1847");
    os_NewLine();
}

void find_date()
{
    os_NewLine();
    os_PutStrFull("MONDAY ");
    switch(current_turn)
    {
    case 0:
        os_PutStrFull("MARCH 29 1847");
        break;
    case 1:
        os_PutStrFull("APRIL 12");
        break;
    case 2:
        os_PutStrFull("APRIL 26");
        break;
    case 3:
        os_PutStrFull("MAY 10");
        break;
    case 4:
        os_PutStrFull("MAY 24");
        break;
    case 5:
        os_PutStrFull("JUNE 7");
        break;
    case 6:
        os_PutStrFull("JUNE 21");
        break;
    case 7:
        os_PutStrFull("JULY 5");
        break;
    case 8:
        os_PutStrFull("JULY 19");
        break;
    case 9:
        os_PutStrFull("AUGUST 2");
        break;
    case 10:
        os_PutStrFull("AUGUST 16");
        break;
    case 11:
        os_PutStrFull("AUGUST 31");
        break;
    case 12:
        os_PutStrFull("SEPTEMBER 13");
        break;
    case 13:
        os_PutStrFull("SEPTEMBER 27");
        break;
    case 14:
        os_PutStrFull("OCTOBER 11");
        break;
    case 15:
        os_PutStrFull("OCTOBER 25");
        break;
    case 16:
        os_PutStrFull("NOVEMBER 8");
        break;
    case 17:
        os_PutStrFull("NOVEMBER 22");
        break;
    case 18:
        os_PutStrFull("DECEMBER 6");
        break;
    case 19:
        os_PutStrFull("DECEMBER 20");
        break;
    case 20:
        os_PutStrFull("YOU HAVE BEEN ON THE TRAIL TOO LONG ------");
        os_NewLine();
        os_PutStrFull("YOUR FAMILY DIES IN THE FIRST BLIZZARD OF WINTER");
        os_NewLine();
        break;
    }
    os_PutStrFull("1847");
}

void hunting_subrout()
{
    int random_word;
    char shooting_words[4][5] = 
    {
        "BANG",
        "BLAM",
        "POW",
        "WHAM"
    };

    if(ammo_spending > 39)
    {
        total_mileage -= 45;

        random_word = rintf(4);
        os_NewLine();
        os_PutStrFull("TYPE ");
        os_PutStrFull(shooting_words[random_word]);
        timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
        // Chooses random word from a list and prints it
        // char random_word[5] = shooting_words[random(1, 4)];
        // os_PutStrFull(random_word);
    }else
    {
        os_NewLine();
        os_PutStrFull("TOUGH---YOU NEED MORE BULLETS TO GO HUNTING");
    }
}

void fort_stop_subrout()
{

}

void main_loop()
{
    os_NewLine();

    if(food_spending < 0)
    {
        food_spending = 0;
    }
    if(ammo_spending < 0)
    {
        ammo_spending = 0;
    }
    if(clothing_spending < 0)
    {
        clothing_spending = 0;
    }
    if(misc_spending < 0)
    {
        misc_spending = 0;
    }
    if(food_spending < 13)
    {
        os_NewLine();
        os_PutStrFull("YOU'D BETTER DO SOME HUNTING OR BUY FOOD SOON!!!!");
    }

    if(illnes_flag || injury_flag)
    {
        cash_left -= 20;
        os_NewLine();
        os_PutStrFull("DOCTOR'S BILL IS $20");
        illnes_flag = false;
        injury_flag = false;
        // Add no money left case
    }

    if(south_pass_flag)
    {
        os_NewLine();
        os_PutStrFull("TOTAL MILEAGE IS 950");
        south_pass_flag = false;
    }else
    {
        os_NewLine();
        os_PutStrFull("TOTAL MILEAGE IS"); // Add printing the mileage
    }

    os_NewLine();
    // I don't think that's how it's actually printed in game
    os_PutStrFull("FOOD, BULLETS, CLOTHING, MISC. SUPP., CASH");
    // Print the variable's values

    if(!fort_option_flag)
    {
        os_NewLine();
        os_PutStrFull("DO YOU WANT TO (1) HUNT, OR (2) CONTINUE");
        switch(get_int_input())
        {
            case 1:

                break;
            case 2:
                break;
        }

    }else
    {
        os_NewLine();
        os_PutStrFull("DO YOU WANT TO (1) STOP AT THE NEXT FORT, (2) HUNT, ");
        os_NewLine();
        os_PutStrFull("OR (3) CONTINUE");
        switch(get_int_input())
        {
        case 1:
            fort_stop_subrout();
            break;
        case 2:
            hunting_subrout();
            break;
        case 3:
            break;
        }
    }
}