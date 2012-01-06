int area(float *a, float *b, float *c, float *A, float *B, float *C) {

	float area;
	
	if (!(*A && *a) && !(*B && *b) && !(*C && *c)) {

		printf("I can't calculate the triangle unless you give ");
		printf("me the area of the triangle:\n");
		printf("Area (0 for unknown): ");
		scanf("%f",&area);

		if (area <= 0) {
			printf("Ok..\n");
			return 1;
		}
		
		if (*A) {
		/* area = 0.5 * b * c * sin A */
	
		if (*b) {
			*c = area/(0.5**b*sin(*A));
		} else {
			*b = area/(0.5*(*c)*sin(*A));
		}
		
		} else if (*B) {
		/* area = 0.5 * a * c * sin B */

		if (*a) {
			*c = area/(0.5**a*sin(*B));
		} else {
			*a = area/(0.5**c*sin(*B));
		}

		} else if (*C) {
		/* area = 0.5 * a * b * sin C */

		if (*a) {
			*b = area/(0.5**a*sin(*C));
		} else {
			*a = area/(0.5**b*sin(*C));
		}

		} else if (*a == 0) {

		*A = asin(area/(0.5**b**c));

		} else if (*b == 0) {

		*B = asin(area/(0.5**a**c));
		
		} else if (*c == 0) {

		*C = asin(area/(0.5**b**a));

		}


		return 0;

	} else {
		printf("Not enough information.\n");
		return 1;
	}


}
