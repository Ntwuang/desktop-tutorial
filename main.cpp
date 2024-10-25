#include <iostream>
#include <cstring>
using namespace std;

//Cấu trúc lưu thông tin ngày sinh
struct Ngay {
    int ngay, thang, nam;
};

//Cấu trúc lưu thông tin sinh viên
struct sinhvien {
    char maSV[10];
    char hoTen[60];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

//Cấu trúc Node trong danh sách liên kết
struct Node {
    sinhvien data;
    Node *link;
};

//Cấu trúc danh sách liên kết
struct List {
    Node *first;
    Node *last;
};


//Tạo node trong danh sách liên kết
Node* taoNode(sinhvien sv) {
    Node *p = new Node;
    if (p != nullptr) {
        p->data = sv;
        p->link = nullptr;
    }
    return p;
}

// Hàm so sánh mã sinh viên để sắp xếp
bool compareMaSV(sinhvien sv1, sinhvien sv2) {
    return strcmp(sv1.maSV, sv2.maSV) < 0;
}

//Khởi tạo hàm nhập ngày sinh
void nhapNgay(Ngay &ngay) {
    cout << "Nhap ngay, thang, nam: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
}

//khởi tạo hàm nhập thông tin sinh viên
void nhapsinhvien(sinhvien &sv) {
    cout << "Nhap ma SV: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten: ";
    cin.ignore();
    cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh (0 - Nu, 1 - Nam): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh:\n";
    nhapNgay(sv.ngaySinh);
    cout << "Nhap dia chi: ";
    cin.ignore();
    cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
}

//khởi tạo hàm thêm sinh viên
void themsinhvien(List &l, sinhvien sv) {
    Node *p = taoNode(sv);
    if (l.first == nullptr || strcmp(sv.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        if (l.last == nullptr)
            l.last = p;
    } else {
        Node *q = l.first;
        while (q->link != nullptr && strcmp(q->link->data.maSV, sv.maSV) < 0) {
            q = q->link;
        }
        p->link = q->link;
        q->link = p;
        if (q == l.last)
            l.last = p;
    }
}

//khởi tạo hàm in danh sách
void inDanhSachSinhVien(const List &l) {
    Node *p = l.first;
    while (p != nullptr) {
        cout << "Ma SV: " << p->data.maSV << ", Ho ten: " << p->data.hoTen << ", Ngay sinh: "
             << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
        p = p->link;
    }
}

//Khởi tạo hàm tìm sinh viên cùng ngày sinh
void timSinhVienCungNgaySinh(const List &l) {
    Node *p = l.first;
    bool found = false;
    while (p != nullptr) {
        Node *q = p->link;
        while (q != nullptr) {
            if (p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                if (p->data.ngaySinh.thang == q->data.ngaySinh.thang) {
                    if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay) {
                        cout << "Ma SV: " << p->data.maSV << ", Ho ten: " << p->data.hoTen << ", Ngay sinh: "
                             << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
                        cout << "Ma SV: " << q->data.maSV << ", Ho ten: " << q->data.hoTen << ", Ngay sinh: "
                             << q->data.ngaySinh.ngay << "/" << q->data.ngaySinh.thang << "/" << q->data.ngaySinh.nam << endl;
                        found = true;
                    }
                }
            }
            q = q->link;
        }
        p = p->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

//Khởi tạo hàm loại bỏ sinh viên cùng ngày sinh
void loaiBoSinhVienCungNgaySinh(List &l) {
    Node *p = l.first;
    Node *prev = nullptr;
    while (p != nullptr) {
        Node *q = p->link;
        bool found = false;
        while (q != nullptr) {
            if (p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                if (p->data.ngaySinh.thang == q->data.ngaySinh.thang) {
                    if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay) {
                        found = true;
                        break;
                    }
                    q = q->link;
                }
                if (found) {
                    if (prev == nullptr) { // xoa o dau danh sach
                        l.first = p->link;
                        delete p;
                        p = l.first;
                    } else { // xoa o giua hoac cuoi
                        prev->link = p->link;
                        delete p;
                        p = prev->link;
                    }
                } else {
                    prev = p;
                    p = p->link;
                }
            }
        }
    }
}
//MAIN
int main() {
    List l;
    l.first = l.last = nullptr;
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        sinhvien sv;
        nhapsinhvien(sv);
        themsinhvien(l, sv);
    }

//in ra danh sách đã nhập
    cout << "\nDanh sach sinh vien sau khi sap xep:\n";
    inDanhSachSinhVien(l);
    
//tim sinh vien cung ngay sinh
    cout << "Sinh vien co cung ngay sinh:\n";
    timSinhVienCungNgaySinh(l);

//xoa sinh vien cung ngay sinh
    cout << "\nXoa sinh vien co cung ngay sinh...\n";
    loaiBoSinhVienCungNgaySinh(l);
    cout << "\nDanh sach sinh vien sau khi xoa:\n";
    inDanhSachSinhVien(l);

    return 0;
}
