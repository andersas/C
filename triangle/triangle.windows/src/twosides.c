/* The next two functions does NO WHAT SO EVER error checking. */

/* Function to rotate the triangle. 
 * Always gets the angle to be angle A.
 * It returns how many turns it has taken (0 - 2)
 */

int rotateleft(float *a, float *b, float *c, float *A, float *B, float *C, int rotations) {

float buffer;

while (rotations > 0) {
/* Rotate sides: */
buffer = *a;
*a = *b;
*b = *c;
*c = buffer;

/* rotate angles: */

buffer = *A;
*A = *B;
*B = *C;
*C = buffer;

/* increase number of rotations: */

rotations--;

}

}


/* Function to rotate the triangle back again.
 * Takes the triangle and the number of rotations to make.
 */

void rotateright(float *a, float *b, float *c, float *A, float *B, float *C, int rotations) {

float buffer;

while (rotations > 0){

/* Rotate sides: */
buffer = *a;
*a = *c;
*c = *b;
*b = buffer;

/* rotate angles: */

buffer = *A;
*A = *C;
*C = *B;
*B = buffer;

rotations--;

}

}

int twosides (float a, float b, float c, float A, float B, float C) {

int rotation = 0; /* always rotate LEFT, and unrotate RIGHT */
float tmp;
int solutions = 0;

if (A) rotation = 0;
if (B) rotation = 1;
if (C) rotation = 2;

rotateleft(&a, &b, &c, &A, &B, &C, rotation);


	if (a && b) {
		/* a/sin(A)=b/sin(B) */
		B = (b*sin(A))/a;
		if (B > 1 || B < -1) goto FAILURE;
		B = asin(B);
		tmp = B;
		if (deg2rad(180)-B+A < deg2rad(180)) {
			/* two solutions */
			solutions++;

			B = deg2rad(180) - B;
			C = deg2rad(180-rad2deg(A)-rad2deg(B));
			c = a*sin(C)/sin(A);
			rotateright(&a, &b, &c, &A, &B, &C, rotation);
			solution(a,b,c,A,B,C,solutions);
			rotateleft(&a, &b, &c, &A, &B, &C, rotation);
			solutions++;
		}
		B = tmp;
		C = deg2rad(180-rad2deg(A)-rad2deg(B));
		c = a*sin(C)/sin(A);
		rotateright(&a, &b, &c, &A, &B, &C, rotation);
		solution(a,b,c,A,B,C,solutions);
		rotateleft(&a, &b, &c, &A, &B, &C, rotation);
		
		return 0;
	}

	if (a && c) {
		/* a/sin(A)=c/sin(C) */
		C = (c*sin(A))/a;
		if (C > 1 || C < -1) goto FAILURE;
		C = asin(C);
		tmp = C;
		if (deg2rad(180)-C+A < deg2rad(180)) {
			/* two solutions*/
			solutions++;

			C = deg2rad(180) - C;
			B = deg2rad(180-rad2deg(A)-rad2deg(C));
			b=a*sin(B)/sin(A);
			rotateright(&a, &b, &c, &A, &B, &C, rotation);
			solution(a,b,c,A,B,C,solutions);
			rotateleft(&a, &b, &c, &A, &B, &C, rotation);
			solutions++;
		}
		C = tmp;
		B = deg2rad(180-rad2deg(A)-rad2deg(C));
		b = a*sin(B)/sin(A);
		rotateright(&a, &b, &c, &A, &B, &C, rotation);
		solution(a,b,c,A,B,C,solutions);
		rotateleft(&a, &b, &c, &A, &B, &C, rotation);
		
		return 0;
	}

	if (b && c) {
		/* a^2 = b^2+c^2-2bc*cos(A) */
		a = sqrt(pow(b,2)+pow(c,2)-2*b*c*cos(A));
		B = (pow(a,2) + pow(c,2) - pow(b,2)) / (2*a*c);
		if (B > 1 || B < -1) goto FAILURE;
		B = acos(B);
		C = deg2rad(180) - A - B;

		rotateright(&a, &b, &c, &A, &B, &C, rotation);
		solution(a,b,c,A,B,C,solutions);
		rotateleft(&a, &b, &c, &A, &B, &C, rotation);
		return 0;
	}


FAILURE:
printf("Impossible triangle!\n");
return 1;

}
