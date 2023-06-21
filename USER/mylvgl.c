/*
 * mylvgl.c
 *
 *  Created on: 2022Äê1ÔÂ26ÈÕ
 *      Author: Sun Lee
 */

#include "myheadfile.h"
#include "headfile.h"

#define MY_DISP_HOR_RES 320
#define MY_DISP_VER_RES 240

#pragma section all "cpu0_dsram"
#pragma section all "cpu0_psram"

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

lv_obj_t * img1_p;
lv_obj_t * img2_p;
lv_obj_t * label1_p;

IFX_ALIGN(4) volatile uint8 mt9v03x_image_for_lvgl[MT9V03X_H][MT9V03X_W];
IFX_ALIGN(4) volatile uint8 mt9v03x_image1_for_lvgl[MT9V03X_H][MT9V03X_W];

//void lv_showimg(uint8 p[MT9V03X_H][MT9V03X_W])
//{
//    uint16 w, h;
//    for(h = 0;h < MT9V03X_H; h++)
//        for(w = 0;w < MT9V03X_W; w++)
//            mt9v03x_image_for_lvgl[h][w] = 255 - p[h][w];
//    lv_img_set_src(img1_p, &my_img_dsc);
//}
//
//void lv_showimg1(uint8 p[MT9V03X_H][MT9V03X_W])
//{
//    uint16 w, h;
//    for(h = 0;h < MT9V03X_H; h++)
//        for(w = 0;w < MT9V03X_W; w++)
//            mt9v03x_image1_for_lvgl[h][w] = 255 - p[h][w];
//    lv_img_set_src(img2_p, &my_img1_dsc);
//}


void lv_ui(void)
{
    /*Create a spinner*/
//    lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
//    lv_obj_set_size(spinner, 20, 20);
//    lv_obj_center(spinner);
//    lv_obj_align(spinner, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    label1_p = label1;
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_obj_align(label1, LV_ALIGN_TOP_RIGHT, 0, 0);
//
//    lv_obj_t * label2 = lv_label_create(lv_scr_act());
//    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
//    lv_obj_set_width(label2, 150);
//    lv_label_set_text(label2, "It is a circularly scrolling text. ");
//    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);

//    lv_obj_t * img1 = lv_img_create(lv_scr_act());
//    img1_p = img1;
//    lv_img_set_src(img1, &my_img_dsc);
//    lv_obj_align(img1, LV_ALIGN_TOP_LEFT, 0, 0);
//    lv_obj_set_size(img1, 188, 120);
//
//    lv_obj_t * img2 = lv_img_create(lv_scr_act());
//    img2_p = img2;
//    lv_img_set_src(img2, &my_img1_dsc);
//    lv_obj_align(img2, LV_ALIGN_BOTTOM_LEFT, 0, 0);
//    lv_obj_set_size(img2, 188, 120);

}

void my_lvinit(void)
{
//    lcd_init();
    ips200_init();
    ips200_clear(WHITE);
    lv_init();
    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;

    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];
    static lv_color_t buf_2[MY_DISP_HOR_RES * 10];

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES*10);

    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = 320;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = 240;                 /*Set the vertical resolution in pixels*/

    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    lv_ui();
}

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
     *`put_px` is just an example, it needs to implemented by you.*/
//    lcd_set_region(area->x1, area->y1, area->x2, area->y2);
    int32_t x, y;
    ips200_address_set(area->x1, area->y1, area->x2, area->y2);
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
//            lcd_writedata_16bit(color_p->full);
            ips200_wr_data16(color_p->full);
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

#pragma section all restore
#pragma section all restore


