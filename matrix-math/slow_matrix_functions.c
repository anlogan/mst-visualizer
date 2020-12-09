#include <stdio.h>
#include <math.h>


//----------------------------------------------------------
//read matrix : cin>> in c++ , scanf() in c
// int cin(float a[100][100]){
// 	int i,j,n;
// 	printf("\n Enter Length Of Matrix N*N : ");
// 	scanf("%d",&n);
// 	printf("\n--------------------------\n");
// 	for(i=0;i<n;i++)
// 		for(j=0;j<n;j++){
// 			printf(" Matrix[%d][%d] : ",i+1,j+1);
// 			scanf("%f",&a[i][j]);
// 		}
// 	printf("\n----------------------------------------------------\n");
// return n;
// }

int cin(int a[3][3]){
    int i,j,n;
    FILE* input_fp;
    input_fp = fopen("diffusion-matrix.txt", "r");
    if (!input_fp) {
        printf("Error opening file\n");
        return 1;
    }
    n = 3;// Size of matrix

    int c;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++){
            c = fgetc(input_fp);
            if (c == 45) { // 45 is a '-', so checking for minus
                c = fgetc(input_fp);
                c = 0 - (2*(c-48));
                a[i][j] = c;
            }
            else {
                a[i][j] = c - 48;
            }
        }
        // This moves the stream forward 1 newline character at the end of each word
        c = fgetc(input_fp);
    }
    return n;
}

int det(int A[32][32], int n)
{
    int Minor[32][32];
    int i,j,k,c1,c2;
    int determinant;
    int c[32];
    int O=1;
    determinant = 0;

    if(n == 2)
    {
        determinant = A[0][0]*A[1][1]-A[0][1]*A[1][0];
        return determinant;
    }
    else
    {
        for(i = 0 ; i < n ; i++)
        {
            c1 = 0, c2 = 0;
            for(j = 0 ; j < n ; j++)
            {
                for(k = 0 ; k < n ; k++)
                {
                    if(j != 0 && k != i)
                    {
                        Minor[c1][c2] = A[j][k];
                        c2++;
                        if(c2>n-2)
                        {
                            c1++;
                            c2=0;
                        }
                    }
                }
            }
            determinant = determinant + O*(A[0][i]*det(Minor,n-1));
            O=-1*O;
        }
    }
    return determinant;
}



//-----------------------------------------------------
// show matrix : cout<< in c++ , printf() in c
void cout(int a[100][100],int n,int show){
    int i,j;
    if(show == 1)
        for(i=0;i < n;i++){
            for(j=0;j < n;j++)
                printf(" %d \t",a[i][j]);
            printf("\n");
        }
    else if(show == 2){
        printf("\n\n The Inverse Of Matrix Is : \n\n");
        for (i=0;i<n;i++){
            for (j=0;j<n;j++)
                printf(" %d \t",a[i][j]);
            printf("\n");
        }
    }
}

//---------------------------------------------------
//	calculate minor of matrix OR build new matrix : k-had = minor
void minor(int b[100][100],int a[100][100],int i,int n){
    int j,l,h=0,k=0;
    for(l=1;l<n;l++)
        for( j=0;j<n;j++){
            if(j == i)
                continue;
            b[h][k] = a[l][j];
            k++;
            if(k == (n-1)){
                h++;
                k=0;
            }
        }
}// end function

//---------------------------------------------------
//	calculate determinte of matrix
int deta(int a[100][100],int n){
    int i;
    int b[100][100],sum=0;
    if (n == 1)
        return a[0][0];
    else if(n == 2)
        return (a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    else
        for(i=0;i<n;i++){
            minor(b,a,i,n);	// read function
            sum = (int) (sum+a[0][i]*pow(-1,i)*det(b,(n-1)));	// read function	// sum = determinte matrix
        }
    return sum;
}// end function

//---------------------------------------------------
//	calculate transpose of matrix
void transpose(int c[100][100],int d[100][100],int n,int det){
    int i,j;
    int b[100][100];
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            b[i][j] = c[j][i];
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            d[i][j] = b[i][j]/det;	// array d[][] = inverse matrix
}// end function

//---------------------------------------------------
//	calculate cofactor of matrix
void cofactor(int a[100][100],int d[100][100],int n,int determinte){
    int b[100][100],c[100][100];
    int l,h,m,k,i,j;
    for (h=0;h<n;h++)
        for (l=0;l<n;l++){
            m=0;
            k=0;
            for (i=0;i<n;i++) {
                for (j=0;j<n;j++)
                    if (i != h && j != l){
                        b[m][k]=a[i][j];
                        if (k<(n-2))
                            k++;
                        else{
                            k=0;
                            m++;
                        }
                    }
                if (pow(-1,(h+l))*det(b,(n-1))) {
                    c[h][l] = 1;
                }
                else { 
                    c[h][l] = 0;
                }
            }// c = cofactor Matrix;
            // c[h][l] = pow(-1,(h+l))*det(b,(n-1));	// c = cofactor Matrix
        }
    transpose(c,d,n,determinte);	// read function
}// end function

//---------------------------------------------------
//	calculate inverse of matrix
void inverse(int a[100][100],int d[100][100],int n,int det){
    if(det == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else if(n == 1)
        d[0][0] = 1;
    else
        cofactor(a,d,n,det);	// read function
}// end function

//---------------------------------------------------
//main fuction exe
int main(void){
    int i,j,n;
    int a[3][3],d[3][3],deter;
    printf("\n C Program To Find Inverse Of Matrix\n\n"); 
    n = cin(a);	// read function
    n = 3;
    int print_matrix = 1;
    printf("Printing read in matrix:\n");
    cout(a,n,print_matrix);	// read function
    deter = (int) det(a,n);	// read function
    printf("----------------------------------------------------\n");
    printf("\n\n Determinant of the Matrix : %d ",deter);
    printf("\n\n-----------------------\n");
    inverse(a,d,n,deter);	// read function
    int print_inverse = 2;
    cout(d,n,print_inverse);	// read function
    printf("\n\n==============================* THE END *==============================\n");
    printf("\n		**** Thanks For Using The Program!!! ****\n");
    return 0;
}// end main
