#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>				//Our primitive header file
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

enum KEYS{ UP, DOWN, LEFT, RIGHT};

int main(int argc, char **argv)
{
	int width = 640;
	int height = 480;
	
	bool done = false;
	bool redraw = true;

	int x = width / 2;
	int y = height / 2;

	int FPS = 60;

	bool keys[4] = {false, false, false, false};

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE *sample3 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;

	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	font18 = al_load_font("Arial.ttf", 18, 0);

	al_reserve_samples(10);

	sample = al_load_sample("chirp.ogg");
	sample2 = al_load_sample("hiphop1.ogg");
	sample3 = al_load_sample("hiphop2.ogg");

	instance1 = al_create_sample_instance(sample);
	instance2 = al_create_sample_instance(sample2);
	instance3 = al_create_sample_instance(sample3);

	al_set_sample_instance_playmode(instance3, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_play_sample_instance(instance3);

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{			
			redraw = true;

			int sx = x;
			int sy = y;

			if(keys[UP])
				y -= 5;
			if(keys[DOWN])
				y += 5;
			if(keys[LEFT])
				x -= 5;
			if(keys[RIGHT])
				x += 5;

			if(sx != x || sy != y)
				al_play_sample_instance(instance1);

			if( x - 10 < 0 || x + 10 > width || y - 10 < 0 || y + 10 > height)
				al_play_sample_instance(instance2);
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			
			al_draw_filled_rectangle(x -10, y -10, x + 10, y + 10, al_map_rgb(255, 0, 255));

			if(al_get_sample_instance_playing(instance1))
				al_draw_text(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "Instance 1 is playing");

			if(al_get_sample_instance_playing(instance2))
				al_draw_text(font18, al_map_rgb(255, 255, 255), width - 5, 5, ALLEGRO_ALIGN_RIGHT, "Instance 2 is playing");

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_sample_instance(instance3);
	al_destroy_sample(sample3);
	al_destroy_sample_instance(instance2);
	al_destroy_sample(sample2);
	al_destroy_sample_instance(instance1);
	al_destroy_sample(sample);
	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}