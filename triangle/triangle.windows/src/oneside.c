int oneside(float a, float b, float c, float A, float B, float C) {

	if (!A) A = deg2rad(180) - B - C;
	if (!B) B = deg2rad(180) - A - C;
	if (!C) C = deg2rad(180) - B - A;

	if (a) {
		/* a/sin(A)=b/sin(B) */
		b = a*sin(B)/sin(A);
		c = sqrt( pow(a,2) + pow(b,2) - 2*a*b*cos(C) );
	} else if (b) {
		/* b/sin(B) = c/sin(C)  */
		c = b*sin(C)/sin(B);
		a = sqrt( pow(b,2) + pow(c,2) - 2*b*c*cos(A) );
	} else if (c) {
		/* c/sin(C)=a/sin(A) */
		a = c*sin(A)/sin(C);
		b = sqrt( pow(a,2) + pow(c,2) - 2*a*c*cos(B) );
	}

	solution(a,b,c,A,B,C,0);
	return 0;

}
