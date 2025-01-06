#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/tokens.h>
#include <string.h>

int oxen_spending, food_spending, ammo_spending, clothing_spending, misc_spending;
int cash_left, total_mileage, bullets, food, clothing, misc_supplies;
int current_turn;
int player_shooting_skill;

void initial_game_setup();
void get_player_shooting_skill();

int main()
{
    os_ClrHome();

    initial_game_setup();
    get_player_shooting_skill();

    return 0;
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
    char input[1];
    os_PutStrFull("HOW GOOD A SHOT ARE YOU WITH YOUR RIFLE?");
    os_NewLine();
    os_PutStrFull("  (1) ACE MARKSMAN,  (2) GOOD SHOT,  (3) FAIR TO MIDDLIN'");
    os_NewLine();
    os_PutStrFull("         (4) NEED MORE PRACTICE,  (5) SHAKY KNEES");
    os_NewLine();
    os_PutStrFull("ENTER ONE OF THE ABOVE -- THE BETTER YOU CLAIM YOU ARE, THE");
    os_NewLine();
    switch(os_GetTokenInput("FASTER YOU'LL HAVE TO BE WITH YOUR GUN TO BE SUCCESSFUL.", input, 1))
    {
        case 1:
        player_shooting_skill = 1;
        break;
        case 2:
        player_shooting_skill = 2;
        break;
        case 3:
        player_shooting_skill = 3;
        break;
        case 4:
        player_shooting_skill = 4;
        break;
        case 5:
        player_shooting_skill = 5;
        break;
    }
}