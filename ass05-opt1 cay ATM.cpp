#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <ctime>
#include <ctype.h>
#include <direct.h>
//STRUCT LUU TAI KHOAN VA MAT KHAU
typedef struct{
	char mSo[50];
	char mPin[40];
} theTu;
//STRUCT LUU THONG TIN CUA MOI TAI KHOAN
typedef struct thongTinTaiKhoan{
    char ten[20];
    int soDuTaiKhoan;
    char loaiTienTe[20];
}taiKhoan;
//CAU TRUC CHUA CAC DUONG LINK MO FILE
typedef struct{
	char taiKhoan[50];
	char giaoDich[50];
	char taiKhoanNhan[50];
	char giaoDichNhan[50];
}linkTaiKhoan;
linkTaiKhoan link;
//CAC HAM SU DUNG
void fn_dangKyTaiKhoan();
void fn_dangNhap();
void fn_daoDich(char *FileName);
void fn_guiTien(char *FileName);
void fn_rutTien(char *FileName);
void fn_chuyenTien(char *FileName);
void menu();
//KHAI BAO THEM BIEN TOAN CUC
char ms[50],mp[20];
int soLuongThe;

//HAM CHI SU DUNG KHI DANG KY MOI TAI KHOAN
void fn_dangKyTaiKhoan(){
	FILE *fp1,*fp2,*fp3;
	theTu tt[50];
	fp1=fopen("TheTu.INP","ab"); //ab: ghi them
    fflush(stdin);
    soLuongThe++;
    printf("Nhap ma so tai khoan: ");gets(tt[soLuongThe].mSo);
    printf("Nhap Mat Khau:");gets(tt[soLuongThe].mPin);
    fwrite(&tt[soLuongThe],sizeof(tt[soLuongThe]),1,fp1);
    fp3=fopen("soLuongThe.INP","w");
    fprintf(fp3,"%d",soLuongThe);
	strcpy(link.taiKhoan,"TaiKhoan/");
    strcat(link.taiKhoan,tt[soLuongThe].mSo);
    strcat(link.taiKhoan,".INP");
	taiKhoan tK;
	fp2=fopen(link.taiKhoan,"wb");
    fflush(stdin);
    printf("Nhap Ten chu Tai khoan: ");gets(tK.ten);
    printf("Nhap so du tai khoan:");
    scanf("%d",&tK.soDuTaiKhoan);fflush(stdin);
    printf("Nhap Loai tien te: ");gets(tK.loaiTienTe);
    fwrite(&tK,sizeof(tK),1,fp2);
    printf("\n\tDang Ky Thanh Cong!!!");
	fclose(fp1);fclose(fp2);fclose(fp3);
}
void fn_dangNhap(){
	FILE *f;
	theTu tt[50];
	int dem=0;
	int check=0;
	f=fopen("TheTu.INP","rb");
	fread(&tt,sizeof(tt),1,f);
    while(check<1&&dem<3){
        printf("\n\t*Nhap Ma so Tai Khoan: ");fflush(stdin);
        gets(ms);
        printf("\t*Nhap Ma PIN:");fflush(stdin);
        gets(mp);
        for(int i=0;i<soLuongThe;i++){
            if(strcmp(tt[i].mSo,ms)==0&&strcmp(tt[i].mPin,mp)==0){
                check=1;
                break;
            }
        }
        dem++;
    }
    if(check==1){
        //CREATE LINK CUA TAI KHOAN DANG DANG NHAP>>chuyen cho fn_daoDich
        strcpy(link.taiKhoan,"TaiKhoan/");
        strcat(link.taiKhoan,ms);
        strcat(link.taiKhoan,".INP");
        strcpy(link.giaoDich,"GiaoDich/");
        strcat(link.giaoDich,ms);
        strcat(link.giaoDich,".INP");
        printf("\tDang Nhap Thanh cong!!!\n");
        fn_daoDich(link.taiKhoan);
    }
    if(dem==3){
        printf("\n\tQua So lan so phep!!");
    }
    fclose(f);
}
void fn_guiTien(char *FileName){
    FILE *f1,*f2,*f3;
    if((f1=fopen(FileName,"r+b"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    if((f2=fopen(link.giaoDich,"ab"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    taiKhoan tK;
    fread(&tK,sizeof(tK),1,f1);
    int tienGui,tongTien;
    printf("\n\tNhap So tien gui:");scanf("%d",&tienGui);
    tongTien = tK.soDuTaiKhoan +tienGui;
    //GHi vao lich su giao dich
    time_t hientai = time(0);
    char* thoiGian= ctime(&hientai);
    fprintf(f2,"\n%s-Gui:%d(VND)-Thoi Gian:%s-Tong So Du %d(%s)\t\t\n"
            ,tK.ten,tienGui,thoiGian,tongTien,tK.loaiTienTe);
    fclose(f1);
    fclose(f2);
    //Ghi lai So tien Vao File Tai khoan
    f3=fopen(FileName,"wb");
    tK.soDuTaiKhoan=tongTien;
    fwrite(&tK,sizeof(tK),1,f3);
    fclose(f3);
    //Hien Thi ra man hinh
    printf("\n-%s\n-Gui:%d(VND)\n-Thoi Gian:%s-Tong So Du %d(%s)\n"
            ,tK.ten,tienGui,thoiGian,tongTien,tK.loaiTienTe);
}
void fn_rutTien(char *FileName){
    FILE *f1,*f2,*f3;
    if((f1=fopen(FileName,"r+b"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    if((f2=fopen(link.giaoDich,"ab"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    taiKhoan tK;
    fread(&tK,sizeof(tK),1,f1);
    int tienRut,tongTien;
    printf("\n\tNhap So tien gui:");scanf("%d",&tienRut);
    tongTien = tK.soDuTaiKhoan -tienRut;
    //GHi vao lich su giao dich
    time_t hientai = time(0);
    char* thoiGian= ctime(&hientai);
    fprintf(f2,"\n%s-Rut:%d(VND)-Thoi Gian:%s-Tong So Du %d(%s)\t\t\n"
            ,tK.ten,tienRut,thoiGian,tongTien,tK.loaiTienTe);
    fclose(f1);
    fclose(f2);
    //Ghi lai So tien Vao File Tai khoan
    f3=fopen(FileName,"wb");
    tK.soDuTaiKhoan=tongTien;
    fwrite(&tK,sizeof(tK),1,f3);
    fclose(f3);
    //Hien Thi ra man hinh
    printf("\n-%s\n-Rut:%d(VND)\n-Thoi Gian:%s-Tong So Du %d(%s)\n"
            ,tK.ten,tienRut,thoiGian,tongTien,tK.loaiTienTe);
}
void fn_chuyenTien(char *FileName){
    FILE *f1,*f2,*f3,*fp;
    if((f1=fopen(FileName,"r+b"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    if((f2=fopen(link.giaoDich,"ab"))==NULL){
        printf("Cannot open file \n\n"); return;
    }
    taiKhoan tK;
    fread(&tK,sizeof(tK),1,f1);
    int tienChuyen,tongTien;
    char taiKhoanNhan[20];
    nhapLai:
    printf("\n\tNhap Tai Khoan chuyen den:");fflush(stdin);
    gets(taiKhoanNhan);
    //Khi nhap dung tai khoan nhan>>> Tao link mo file tai khoan nhan
    strcpy(link.taiKhoanNhan,"TaiKhoan/");
    strcat(link.taiKhoanNhan,taiKhoanNhan);
    strcat(link.taiKhoanNhan,".INP");
    strcpy(link.giaoDichNhan,"GiaoDich/");
    strcat(link.giaoDichNhan,taiKhoanNhan);
    strcat(link.giaoDichNhan,".INP");
    if((fp=fopen(link.taiKhoanNhan,"r+b"))==NULL){
        printf("\n\tTai Khoan nhan Khong hop le!!");
        goto nhapLai;
    }else{
        do{
        printf("\n\tNhap So tien chuyen:");
        scanf("%d",&tienChuyen);
        }while(tienChuyen<1||tienChuyen>tK.soDuTaiKhoan);
        tongTien = tK.soDuTaiKhoan -tienChuyen;
        //Ghi Vao lich Su Giao Dich Cho Tai Khoan chuyen
        time_t hientai = time(0);
        char* thoiGian= ctime(&hientai);
        fprintf(f2,"\n%s-Chuyen:%d(VND)-Toi TK:%s -Thoi Gian:%s-Tong So Du %d(%s)\t\t\n"
                ,tK.ten,tienChuyen,taiKhoanNhan,thoiGian,tongTien,tK.loaiTienTe);
        fclose(f1);
        fclose(f2);
        //Cap Nhat Lai So Tien Sau Khi Chuyen Cho Tai Khoan Chuyen (Tru di)
        f3=fopen(FileName,"wb");
        tK.soDuTaiKhoan=tongTien; //Tien da chuyen duoc cap nhap vao tai khoan
        fwrite(&tK,sizeof(tK),1,f3);
        fclose(f3);
        //Hien Thi ra man hinh---------------------------------------------------------
        printf("\n-%s \n-chuyen:%d(VND)\n-Toi TK: %s\n-Thoi Gian:%s-Tong So Du %d(%s)\n"
                ,tK.ten,tienChuyen,taiKhoanNhan,thoiGian,tongTien,tK.loaiTienTe);
        //Cap Nhat So Tien Cho Tai Khoan Nhan (Cong Them Vao)---------------------
        fread(&tK,sizeof(tK),1,fp);
        tK.soDuTaiKhoan+=tienChuyen;//tK.soDuTaiKhoan se khac voi o tren because open *fp
        if((fp=fopen(link.taiKhoanNhan,"wb"))==NULL){
            printf("Cannot open file tai khoan nhan!!\n\n"); return;
        }
        fwrite(&tK,sizeof(tK),1,fp);
        //Ghi Lich Su Giao Dich Cho Tai Khoan Nhan-----------------------------------------
        FILE *fp2;
        if((fp2=fopen(link.giaoDichNhan,"ab"))==NULL){
            printf("Cannot open file giaodich nhan!!\n\n"); return; //mo de ghi
        }
        fprintf(fp2,"\nBan da nhan:%d(VND)-Tu TK:%s -Thoi Gian:%s-Tong So Du %d(%s)\t\t\n"
                ,tienChuyen,ms,thoiGian,tongTien,tK.loaiTienTe);
        fclose(fp2);
        //Hien Thi ra man hinh----------------------------------------------------------
        printf("\n-%s \n-Nhan:%d(VND)\n-tu TK: %s\n-Thoi Gian:%s\n-Tong so du:%d\n"
                ,tK.ten,tienChuyen,ms,thoiGian,tK.soDuTaiKhoan);
        fclose(fp);
    }
}
void fn_daoDich(char *FileName){
    FILE *fp;
    taiKhoan tK;
    if((fp=fopen(FileName,"rb"))==NULL){
        printf("\nKhong Mo dc file!!");
    }
    fread(&tK,sizeof(tK),1,fp);
    fclose(fp);
    printf("\n\t\t===>CHAO MUNG %s<===",tK.ten);//toupper(ten)
    printf("\n\n\tSo Tien Hien Tai Trong Tai khoan la: %d (%s)\n",tK.soDuTaiKhoan,tK.loaiTienTe);
    int luaChon;
    do{
        printf("\n\t\t|==>Moi Ban chon Phuong Thuc<==|");
        printf("\n\t\t\t1.Gui Tien");
        printf("\n\t\t\t2.Rut Tien");
        printf("\n\t\t\t3.Chuyen Tien");
        printf("\n\t\t\t4.Thoat!");
        do{
            printf("\n\tChoose service:");
            fflush(stdin);
            scanf("%d",&luaChon);
        }while(luaChon<1||luaChon>4);
        switch(luaChon){
            case 1:
                fn_guiTien(FileName);
                break;
            case 2:
                fn_rutTien(FileName);
                break;
            case 3:
                fn_chuyenTien(FileName);
                break;
        }
    }while(luaChon!=4);
}
void menu(){
    int luachon;
    do{
    printf("\n==========>Welcome to Van Hau bank ATM System:<==========\n");
    printf("\t\t\t1. Dang Nhap\n");
    printf("\t\t\t2. Dang ky Tai Khoan\n");
    printf("\t\t\t3. Thoat\n");
    printf("\n\t\tChoose service: ");
    scanf("%d",&luachon);
    switch(luachon){
        case 1:
            fn_dangNhap();
            break;
        case 2:
            fn_dangKyTaiKhoan();
            break;
        }
    }while(luachon!=3);
    printf("\n\tThanks you! see you again!!!\n\n");
}
int main(){
    //Chay lan dau can tao:
    /*FILE *fpp1=fopen("soLuongThe.INP","w");
    fprintf(fpp1,"%d",0);
    fclose(fpp1);
    //Tao forder:(chay lan dau)
    _mkdir ("TaiKhoan");
    _mkdir ("GiaoDich");
    */
    FILE *fpp=fopen("soLuongThe.INP","r");
    fscanf(fpp,"%d",&soLuongThe);
    fclose(fpp);
    menu();
    //TAI KHOAN DA DANG KY
    //Hau:      12345678912345     mk:123456
    //Du :      01234567891234     mk:012345
    //Tuong :   11223344556677     mk:123321
    //CAM :     12345671234567     mk:111111

}
