#include <iostream>
#include <vector>
using namespace std;

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = -m; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

void getCofactor(vector<vector<int>> &a, vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = a[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>> &a, int n, int N)
{
    int D = 0;
    if (n == 1)
        return a[0][0];
    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;
    for (int f = 0; f < n; f++)
    {
        getCofactor(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}

void adjoint(vector<vector<int>> &a, vector<vector<int>> &adj, int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int>> temp(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(a, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1, N));
        }
    }
}

bool inverse(vector<vector<int>> &a, vector<vector<int>> &inv, int N)
{
    int det = determinant(a, N, N);
    if (det == 0)
    {
        cout << "Inverse does not exist";
        return false;
    }
    int invDet = modInverse(det, 26);
//    cout << det % 26 << ' ' << invDet << '\n';
    vector<vector<int>> adj(N, vector<int>(N));
    adjoint(a, adj, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = (adj[i][j] * invDet) % 26;
    return true;
}

int main()
{
mulai:
	int n= 2;
    vector<vector<int>> pl(n, vector<int>(n));
    vector<vector<int>> adj(n, vector<int>(n));
    vector<vector<int>> inv(n, vector<int>(n));
    
	string p,c;
    
    cout<<"Silahkan masukan plaintext (Huruf Kapital): "; cin>>p;
    cout<<"Silahkan masukan ciphertext (Huruf Kapital): "; cin>>c;

    int helper=0;
    int ci[2][2], pli[2][2], output[2][2];
    for(int i= 0 ; i < 2; i++){
    	for(int j= 0 ; j < 2; j++){

    		ci[j][i]= c[helper]-'A';
			pl[j][i]= p[helper]-'A';
    		helper++;
		}
		
	}
	helper=0;
	
    //plaintext
    cout<<"\nPlaintext"<<endl;
	for(int i= 0 ; i < n; i++){
    	for(int j= 0 ; j < n; j++){
    		cout<<pl[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//ciphertext
	cout<<"\nCiphertext"<<endl;
	for(int i= 0 ; i < n; i++){
    	for(int j= 0 ; j < n; j++){
    		cout<<ci[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//inverse plaintext
	if(inverse(pl,inv,n)){
		cout<<"\n";
	}
	cout<<"\nInverse Plaintext"<<endl;
	for(int i= 0 ; i < n; i++){
    	for(int j= 0 ; j < n; j++){
			inv[i][j]= (inv[i][j]+26) % 26;
    		cout<<inv[i][j]<<" ";
			
    		
		}
		cout<<endl;
	}

	for(int i= 0 ; i < 2; i++){
    	for(int j= 0 ; j < 2; j++){
    		output[i][j] = 0;
		}
	}
	
	//perkalian ciphertext dengan inverse plaintext
	for(int i= 0 ; i < 2; i++){
    	for(int j= 0 ; j < 2; j++){
    		for(int k= 0 ; k < 2; k++){
    			output[i][j]+=ci[i][k] * inv[k][j];
			}
		}
	}
	
	//menampilkan key sebelum mod 26
	cout<<"\nKey sebelum di mod 26"<<endl;
    for(int i= 0 ; i < 2; i++){
    	for(int j= 0 ; j < 2; j++){
    		cout<<output[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//menampilkan key setelah di mod 26
	cout<<"\nKey setelah di mod 26"<<endl;
	for(int i= 0 ; i < 2; i++){
    	for(int j= 0 ; j < 2; j++){
    		cout<<output[i][j]%26<<" ";
		}
		cout<<endl;
	}
    
    //Perulangan untuk memulai program kembali atau keluar program
    string pilih;
    cout << "\n\nApakah ingin diulang ? (Y/N) ";
    cin >> pilih;
    if (pilih == "Y" || pilih == "y")
    {
        goto mulai;
    }
    else
    {
        return 0;
    }
}
