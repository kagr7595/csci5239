struct Vertex
{
    float xyz[3];
    float rgba[4];
};

// Cube as 12 triangles
const Vertex Vertices[] =
{
   //  Front
   {{-1,-1, 1},{1,0,0,1}},
   {{+1,-1, 1},{1,0,0,1}},
   {{-1,+1, 1},{1,0,0,1}},
   {{-1,+1, 1},{1,0,0,1}},
   {{+1,-1, 1},{1,0,0,1}},
   {{+1,+1, 1},{1,0,0,1}},
   //  Back
   {{+1,-1,-1},{0,0,1,1}},
   {{-1,-1,-1},{0,0,1,1}},
   {{+1,+1,-1},{0,0,1,1}},
   {{+1,+1,-1},{0,0,1,1}},
   {{-1,-1,-1},{0,0,1,1}},
   {{-1,+1,-1},{0,0,1,1}},
   //  Right
   {{+1,-1,+1},{1,1,0,1}},
   {{+1,-1,-1},{1,1,0,1}},
   {{+1,+1,+1},{1,1,0,1}},
   {{+1,+1,+1},{1,1,0,1}},
   {{+1,-1,-1},{1,1,0,1}},
   {{+1,+1,-1},{1,1,0,1}},
   //  Left
   {{-1,-1,-1},{0,1,0,1}},
   {{-1,-1,+1},{0,1,0,1}},
   {{-1,+1,-1},{0,1,0,1}},
   {{-1,+1,-1},{0,1,0,1}},
   {{-1,-1,+1},{0,1,0,1}},
   {{-1,+1,+1},{0,1,0,1}},
   //  Top
   {{-1,+1,+1},{0,1,1,1}},
   {{+1,+1,+1},{0,1,1,1}},
   {{-1,+1,-1},{0,1,1,1}},
   {{-1,+1,-1},{0,1,1,1}},
   {{+1,+1,+1},{0,1,1,1}},
   {{+1,+1,-1},{0,1,1,1}},
   //  Bottom
   {{-1,-1,-1},{1,0,1,1}},
   {{+1,-1,-1},{1,0,1,1}},
   {{-1,-1,+1},{1,0,1,1}},
   {{-1,-1,+1},{1,0,1,1}},
   {{+1,-1,-1},{1,0,1,1}},
   {{+1,-1,+1},{1,0,1,1}},
};
