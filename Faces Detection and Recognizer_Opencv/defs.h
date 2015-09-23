#ifndef DEFS_H

/** Inputs: **/
#define CASCADE_PATH_FACE  "cascade/haarcascade_frontalface_alt2.xml"
#define TRAINING_LISTFRAME "Dection_faces/listframe"
#define TRAINING_LISTNAME "Dection_faces/listname"

/** Output face and name: **/
#define OUTPUT_DIR "Dection_faces"
#define OUTPUT_LISTFRAME "listframe"
#define OUTPUT_LISTNAME "listname"
#define FACE_SIZE Size(150,150)

/** Colors, fonts... **/
#define NO_MATCH_COLOR    Scalar(0,0,255) //red
#define MATCH_COLOR       Scalar(0,255,0) //green
#define FONT              FONT_HERSHEY_PLAIN

/** Face detector: **/
#define DET_SCALE_FACTOR   1.1
#define DET_MIN_NEIGHBORS  3

/** LBPH face recognizer: **/
#define LBPH_RADIUS    3
#define LBPH_NEIGHBORS 8
#define LBPH_GRID_X    8
#define LBPH_GRID_Y    8
#define LBPH_THRESHOLD 180.0

#endif	/* DEFS_H */

