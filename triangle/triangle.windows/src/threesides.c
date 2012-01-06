int threesides (float a, float b, float c, int solutions) {

	float A,B,C;

	/* We have all the sides! */

	if (a >= b+c || b >= a+c || c >= a+b) {
		printf("No solution\n");
		return 1;
	}

	A = acos( (pow(b,2) + pow(c,2) - pow(a,2)) / (2*b*c) );
	B = acos( (pow(a,2) + pow(c,2) - pow(b,2)) / (2*a*c) );
	C = acos( (pow(b,2) + pow(a,2) - pow(c,2)) / (2*b*a) );

	solution(a,b,c,A,B,C,solutions); 
	
	return 0;

}
