#include<iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct List {
    Node* first;
    Node* last;
};

// Hàm so sánh chuỗi 
int sosanhchuoi(const char* chuoi1, const char* chuoi2) {
    while (*chuoi1 && (*chuoi1 == *chuoi2)) {
        chuoi1++;
        chuoi2++;
    }
    return *(unsigned char*)chuoi1 - *(unsigned char*)chuoi2;
}

// Khởi tạo danh sách rỗng
void danhsachrong(List& list) {
    list.first = NULL;
    list.last = NULL;
}

// Hàm nhập thông tin sinh viên
SinhVien nhapthongtin() {
    SinhVien sv;
    cout << "Nhap MSSV: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten sinh vien: ";
    cin >> sv.hoTen;
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;
    cout << "Nhap Ngay Thang Nam Sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Nhap dia chi sinh vien: ";
    cin >> sv.diaChi;
    cout << "Nhap lop sinh vien: ";
    cin >> sv.lop;
    cout << "Nhap khoa sinh vien: ";
    cin >> sv.khoa;
    return sv;
}

// Hàm in thông tin sinh viên
void inthongtin(SinhVien sv) {
    cout << "MSSV: " << sv.maSV << endl;
    cout << "Ho va ten: " << sv.hoTen << endl;
    cout << "Gioi tinh: " << (sv.gioiTinh == 1 ? "Nam" : "Nu") << endl;
    cout << "Ngay sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << endl;
    cout << "Dia chi: " << sv.diaChi << endl;
    cout << "Lop: " << sv.lop << endl;
    cout << "Khoa: " << sv.khoa << endl;
}

// Hàm thêm sinh viên vào danh sách đã sắp xếp
void themsinhvien(List& list, SinhVien sv) {
    Node* newnode = new Node;
    newnode->data = sv;
    newnode->link = NULL;

    // Nếu danh sách rỗng
    if (list.first == NULL) {
        list.first = list.last = newnode;
        return;
    }

    Node* current = list.first;
    Node* prev = NULL;

    // Tìm vị trí để chèn sinh viên vào danh sách đã sắp xếp
    while (current != NULL && sosanhchuoi(current->data.maSV, sv.maSV) < 0) {
        prev = current;
        current = current->link;
    }

    // Chèn vào đầu danh sách
    if (prev == NULL) {
        newnode->link = list.first;
        list.first = newnode;
    }
    // Chèn vào giữa hoặc cuối
    else {
        prev->link = newnode;
        newnode->link = current;
    }

    // Cập nhật "last" nếu chèn ở cuối danh sách
    if (current == NULL) {
        list.last = newnode;
    }
}

// Hàm in danh sách sinh viên
void indanhsachsinhvien(List list) {
    Node* current = list.first;
    while (current != NULL) {
        inthongtin(current->data);
        cout << endl;
        current = current->link;
    }
}

// Hàm tìm sinh viên có cùng ngày sinh
void timkiemcungngaysinh(List list, Ngay date) {
    Node* current = list.first;
    bool timthay = false;

    while (current != NULL) {
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {
            inthongtin(current->data);
            timthay = true;
        }
        current = current->link;
    }

    if (!timthay) {
        cout << "Khong tim thay sinh vien co cung ngay sinh" << endl;
    }
}

// Hàm xóa sinh viên có cùng ngày sinh
void xoasinhviencungngaysinh(List& list, Ngay date) {
    Node* current = list.first;
    Node* prev = NULL;
    bool timthay = false;

    while (current != NULL) {
        // Nếu sinh viên có ngày sinh trùng khớp
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {

            timthay = true;

            // Xóa sinh viên đầu danh sách
            if (prev == NULL) {
                list.first = current->link;
                delete current;
                current = list.first;
            }
            // Xóa sinh viên giữa hoặc cuối
            else {
                prev->link = current->link;
                delete current;
                current = prev->link;
            }

            // Cập nhật con trỏ last nếu xóa ở cuối danh sách
            if (current == NULL) {
                list.last = prev;
            }
        }
        else {
            prev = current;
            current = current->link;
        }
    }

    if (!timthay) {
        cout << "Khong tim thay sinh vien nao co cung ngay sinh de xoa!" << endl;
    }
}

int main() {
    List list;
    danhsachrong(list);

    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    // Nhập danh sách sinh viên và thêm vào danh sách đã sắp xếp
    for (int i = 0; i < n; i++) {
        SinhVien sv = nhapthongtin();
        themsinhvien(list, sv);
    }
    cout << endl;

    // In danh sách sinh viên đã sắp xếp
    cout << "Danh sach sinh vien sau khi sap xep theo ma SV:" << endl;
    indanhsachsinhvien(list);
    cout << endl;

    // Thêm một sinh viên mới và giữ danh sách sắp xếp
    cout << "Nhap thong tin sinh vien moi: " << endl;
    SinhVien sv = nhapthongtin();
    themsinhvien(list, sv);

    // In lại danh sách sau khi thêm sinh viên mới
    cout << "Danh sach sinh vien sau khi them sinh vien moi:" << endl;
    indanhsachsinhvien(list);
    cout << endl;

    // Tìm sinh viên có cùng ngày sinh
    Ngay ngay;
    cout << "Nhap ngay sinh (dd mm yyyy) de tim sinh vien: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
    cout << "Sinh vien co cung ngay sinh: " << endl;
    timkiemcungngaysinh(list, ngay);
    cout << endl;

    // Xóa sinh viên có cùng ngày sinh
    cout << "Nhap ngay sinh (dd mm yyyy) de xoa sinh vien: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
    xoasinhviencungngaysinh(list, ngay);
    cout << "Danh sach sinh vien sau khi xoa sinh vien co cung ngay sinh:" << endl;
    indanhsachsinhvien(list);

    return 0;
}
