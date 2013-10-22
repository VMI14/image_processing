/*
 * This program implements a number of image processing algorithms on
 * fixed-size 256x256 greyscale images.
 *
 * Author: Mac Baker
 * Date: 10/9/2013
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Define some constants for the available operations
#define READ      1
#define WRITE     2
#define INVERSE   3
#define ROTATE    4
#define LOWPASS   5
#define HIGHPASS  6
#define MEDIAN    7
#define ZOOM      8
#define TILE      9
#define EDGE      10
#define THRESH    11      
#define HISTO     12
#define EXIT      13



// function prototypes for the PGM I/O functions
void readPGMImage( char name[], unsigned char image[256][256] );
void writePGMImage( char name[], unsigned char image[256][256] );

// function prototypes for the image processing functions
// YOU NEED TO SUPPLY IMPLEMENTATIONS OF ALL OF THESE! See below.
int getMenuSelection(void);
void inverse( unsigned char image[256][256] );
void rotate( unsigned char image[256][256] );
void lowpass( unsigned char image[256][256] );
void highpass( unsigned char image[256][256] );
void median( unsigned char image[256][256] );
void zoom( unsigned char image[256][256] );
void tile( unsigned char image[256][256] );
void edge( unsigned char image[256][256] );
void thresh( unsigned char image[256][256] );
void histo( unsigned char image[256][256] );


// main -- print menu, get user's selection, and process it.
int main(void)
{
   unsigned char image[256][256];   // array to hold image data
   int choice;                      // menu choice from user
   char filename[80];               // filename entered by user
   
   do {
      // print menu and get user's selection
      choice = getMenuSelection();
      
      // returned value should be between READ and EXIT
      assert( choice >= READ && choice <= EXIT );
      
      // process the selection
      switch (choice) {
         case READ:     // get filename from the user
                        printf("Enter the filename to read: ");
                        scanf("%79s", filename);
                        readPGMImage( filename, image );
                        break;
                        
         case WRITE:    // get filename from the user
                        printf("Enter the filename to write: ");
                        scanf("%79s", filename);
                        writePGMImage( filename, image );
                        break;
                        
         case INVERSE:  inverse( image );
                        break;
                        
         case ROTATE:   rotate( image );
                        break;
                        
         case LOWPASS:  lowpass( image );
                        break;
                        
         case HIGHPASS: highpass( image );
                        break;
                        
         case MEDIAN:   median( image );
                        break;
                        
         case ZOOM:	    zoom( image );
         			    break;
         			    
         case TILE:	    tile( image );
         			    break;
         	
         case EDGE:	    edge( image );
         			    break;
         			    
         case THRESH:   thresh( image );
         			    break;
         			    
         case HISTO:    histo( image );
         			    break;			                   
                        
         default:       // do nothing
                        break;
      }
   } while ( choice != EXIT );      // repeat until they exit
   
   return 0;
}



/*
 * readPGMImage -- This routine is used to read an image from a PGM file.
 * Note that it only works for 256x256 greyscale images.
 * Input: name = filename for image file
 *        image = 256x256 array of unsigned chars, used to store image data
 * Output: no return value, but function modifies image array
 * Author: Mac Baker
 */
void readPGMImage( char name[], unsigned char image[256][256] )
{
   FILE *fp;
   int i, j;
   int width, height, depth;

   // open the file
   fp = fopen( name, "r" );
   if ( fp == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open input file %s\n", name);
      exit(1);
   }

   // read PGM header stuff
   if ( fscanf(fp, "P5 %d%d%d\n", &width, &height, &depth) != 3 ) {
      fprintf(stderr, "ERROR -- Cannot read input file %s -- invalid .pgm file\n",
                 name);
      exit(1);
   }

   if ( (width > 256) || (height > 256) || (depth > 255) ) {
      fprintf(stderr, "ERROR -- Cannot read input file %s -- unsupported .pgm file\n",
		name);
      exit(1);
   }

   for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         if ( feof( fp ) ) {
            fprintf(stderr, "ERROR -- Invalid input file %s.\n", name);
            exit(1);
         }
         else {
            image[i][j] = getc(fp);
         }
      }

      // fill in rest of row if needed
      for ( j = width; j < 256; j++ ) {
         image[i][j] = 0;
      }
   }

   // if image is less than 256x256, fill in other spots
   for ( i = height; i < 256; i++ ) {
      for ( j = 0; j < 256; j++ ) {
         image[i][j] = 0;
      }
   }

   // close file
   fclose( fp );
}


/*
 * writePGMImage -- This function writes an image out as a PGM file. It assumes
 * the image is 256x256 greyscale.
 * Input: name = filename to write to
 *        image = 256x256 array containing image data
 * Output: none
 * Author: Mac Baker
 */
void writePGMImage( char name[], unsigned char image[256][256] )
{
   int i, j;
   FILE *fp;

   // open the file
   fp = fopen( name, "w" );
   if( fp == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open output file %s\n", name);
      exit(1);
   }

   // write PGM header
   fprintf(fp, "P5\n256 256\n255\n");

   // write image data
   for ( i = 0; i < 256; i++ ) {
      for ( j = 0; j < 256; j++ ) {
         putc( image[i][j], fp );
      }
   }

   // close the file
   fclose( fp );
}
        
// Stub functions so that the program can be compiled. Be sure to include the real implementations of all of these functions.

/*
 * Print the menu, get the menu choice from the user, and return it.
 * Input: none
 * Returns menu selection from user (a number from 1 to 8).
 */
int getMenuSelection(void)
{
   int getMenuOption;
   
   printf("Welcome to Image Processing.\n");
   printf("Enter 1 to read the program.\n");
   printf("Choices:\n 3. Inverse\n 4. Rotate\n 5. Lowpass\n 6. Highpass \n 7. Median\n");
   printf("Enter 2 to write the program.\n");
   printf("Enter 13 to exit.\n");
     
     scanf("%d", &getMenuOption);
 
   return getMenuOption;
}
/*
 * Take the inverse of an image.
 * Input: image = array holding the image data
 * Returns nothing, but modifies the image array
 *the pocket handbook image processing c progr
 am
 */
void inverse( unsigned char image[256][256] )

{
int i, j;
	
	for(i=0; i<256; i++){
	   for (j=0; j<256; j++) {
   	      image[i][j] = 255-image[i][j];
   	   }
   	}
}

void rotate( unsigned char image[256][256] )
{
int i, j;
unsigned char rotate[256][256];
	//rotate clockwise
	for(i=0; i<256; i++){
		for(j=0; j<256; j++){
			rotate[i][j]=image[255-j][i];			
		}
	}
	for(i=0; i<256; i++){
		for(j=0; j<256; j++){
			image[i][j] = rotate[i][j];
		}
	}		
}

void lowpass( unsigned char image[256][256] )
{

int i, j;
unsigned char lowpass[256][256];

	for(i=1; i<255; i++){
		for(j=1; j<255; j++){
			lowpass[i][j]=(image[i-1][j-1]+image[i-1][j]+image[i-1][j+1]+image[i][j-1]+image[i][j]+image[i][j+1]+image[i+1][j-1]+image[i+1][j]+image[i+1][j+1])/9;
		}
	}
			
	for(i=0; i<255; i++){
		for(j=0; j<255; j++){
			image[i][j]=lowpass[i][j];
		}
	}
}

void highpass( unsigned char image[256][256] )
{
int i, j;
int highpass[256][256];

	for(i=1; i<255; i++){
		for(j=1; j<255; j++){
			highpass[i][j]=9*image[i][j]-image[i-1][j-1]-image[i-1][j]-image[i-1][j+1]-image[i][j-1]-image[i][j+1]-image[i+1][j-1]-image[i+1][j]-image[i+1][j+1];
			if (highpass[i][j] < 0){
				highpass[i][j]= 0;}
			else if( highpass[i][j] > 255){
				highpass[i][j]=255;}		
		}
	}
			
	for(i=0; i<255; i++){
		for(j=0; j<255; j++){
		image[i][j]=highpass[i][j];
		}
	}
}

void median( unsigned char image[256][256] )
{

int i, j;
int median [256][256];

for(i=1; i<255; i++){
		for(j=1; j<255; j++){
			int values[] = { image[i-1][j-1],image[i-1][j],image[i-1][j+1], image[i][j-1],image[i][j],image[i][j+1],image[i+1][j-1],image[i+1][j],image[i+1][j+1] };
		
		for ( c = 0 ; c < n ; c++ )
		{
      		scanf("%d", &array[c]);
 
   			for ( c = 0 ; c < ( n - 1 ) ; c++ )
   			{
     		 	position = c;
 
     			for ( d = c + 1 ; d < n ; d++ )
     			{
       				if ( array[position] > array[d] ){
            				position = d;}
     	 		}
     	 	}
     	 	
     	 	if ( position != c )
     	 	{
         			swap = array[c];
       			array[c] = array[position];
         			array[position] = swap;
      	  	}
            }
   			  median[i][j] = values[4];
}
}
//http://www.programmingsimplified.com/c/source-code/c-program-selection-sort

void zoom( unsigned char image[256][256])
{
}

void tile( unsigned char image[256][256])
{
}

void edge( unsigned char image[256][256])
{
}

void thresh( unsigned char image[256][256])
{
}

void histo( unsigned char image[256][256])
{
}

