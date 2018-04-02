struct face {
	int p1;
	int p2;
	int p3;
};

struct object {
	struct point* points;
	struct face* faces;
};

