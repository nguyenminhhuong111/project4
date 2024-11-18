#include<iostream>
using namespace std;
//Khai báo cấu trúc danh sách liên kết từ
struct tu {
    string vol;  // Vocabulary
    tu* next;
};
//Khai báo cấu trúc danh sách liên kết câu là 1 danh sách gồm nhiều node từ
struct cau {
    tu* head;
};
// Khởi tạo danh sách câu
void khoitaocau(cau* cau) {
    cau->head = NULL;
}
// Thêm từ vào danh sách liên kết
void them_tu(cau* cau, string vol) {
    tu* newtu = new tu;
    newtu->vol = vol;
    newtu->next = NULL;
    //Nếu câu rỗng thêm vào đầu
    if (cau->head == NULL) {
        cau->head = newtu;
    }
    //Thêm vào sau từ có trước
	else {
        tu* temp = cau->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newtu;
    }
}
// Tạo một cấu trúc lưu dữ liệu từ và số lần từ đó xuất hiện trong câu
struct infor {
    string vol;
    int solan;
    infor* next;
};
//Tạo 1 danh sách lưu thông tin của các từ
struct listinfor {
    infor* head;
};
// Khởi tạo danh sách liên kết chứa thông tin về từ
void list_infor(listinfor* listinfor) {
    listinfor->head = NULL;
}
// Kiểm tra xem từ đã có trong danh sách chưa
bool kiemtra_tu(listinfor* list, string vol) {
    infor* temp = list->head;
    while (temp != NULL) {
        if (temp->vol == vol) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Xác định từ xuất hiện nhiều nhất trong câu
void Tim_tu_xuat_hien_nhieu_nhat(cau* cau, listinfor* listinfor) {
    tu* tu1 = cau->head;
    if (tu1 == NULL) return;
    // Sử dụng mảng để đếm số lần xuất hiện mỗi từ
    int cnt[100] = {0}; //Khởi tạo mảng đếm lưu được 100 từ
    int index = 0;//Khởi tạo biến đếm
    // Đếm tần suất xuất hiện của các từ
    // Thuật toán :
    //Tạo 2 bản sao của danh sách câu đó duyệt từng từ của danh sách 1 xem có trùng với từng từ của danh sách 2 
    //Sau khi duyệt hết danh sách 2 lại chuyển sang node kế tiếp của danh sách 1 rồi lại làm tương tự
    //Mỗi lần nhu vậy thu được số lần xuất hiện của mỗi từ
    while (tu1 != NULL) {
        tu* tu2 = cau->head;
        while (tu2 != NULL) {
            if (tu2->vol == tu1->vol) {
                cnt[index]++;
            }
            tu2 = tu2->next;
        }
        // Kiểm tra nếu từ chưa có trong danh sách
        if (!kiemtra_tu(listinfor, tu1->vol)) {
            // Thêm từ vào danh sách infor nếu chưa có
            infor* newinfor = new infor;
            newinfor->vol = tu1->vol;
            newinfor->solan = cnt[index];
            newinfor->next = listinfor->head;
            listinfor->head = newinfor;
        }
        index++;
        tu1 = tu1->next;
    }
    // Tìm từ có số lần xuất hiện lớn nhất
    infor* temp = listinfor->head;
    int max_count = 0;
    while (temp != NULL) {
        if (temp->solan > max_count) {
            max_count = temp->solan;
        }
        temp = temp->next;
    }

    // In ra các từ có số lần xuất hiện nhiều nhất
    temp = listinfor->head;
    cout << "Tu duoc xuat hien nhieu nhat la: ";
    while (temp != NULL) {
        if (temp->solan == max_count) {
            cout << "'" << temp->vol << "'" << " voi so lan la : " << temp->solan << endl;
        }
        temp = temp->next;
    }
}
//Loại bỏ từ nếu xuất hiện từ láy
void loai_bo_tu_lay(cau* cau) {
    if (cau->head == NULL || cau->head->next == NULL) return;
    tu* tu1 = cau->head;
    while (tu1 != NULL && tu1->next != NULL) {
        // Kiểm tra nếu node hiện tại trỏ tới chính nó
        if (tu1->next->vol == tu1->vol) {
            tu* temp = tu1->next;
            tu1->next = temp->next;  // Bỏ qua node lặp
            delete temp;
        } else {
            tu1 = tu1->next;  // Chuyển sang node tiếp theo
        }
    }

    // In danh sách sau khi xử lý
    tu* temp = cau->head;
    cout<<"Cau sau khi loai bo tu lay la :";
    while (temp != NULL) {
        cout <<temp->vol << " ";
        temp = temp->next;
    }
    cout << endl;
}
//Đếm số từ xuất hiện trong câu
void dem_so_tu_xuat_hien_trong_cau(cau* cau){
	int sotu = 0;
	tu* temp = cau->head;
	while(temp != NULL){
		sotu++;
		temp = temp->next;
	}
	cout<<"So tu xuat hien trong cau la : "<<sotu<<endl;
}
int main() {
    cau cau1;
    khoitaocau(&cau1);
    // Thêm các từ vào danh sách câu
    them_tu(&cau1, "nguyen");
    them_tu(&cau1, "minh");
    them_tu(&cau1, "huong");
    them_tu(&cau1, "dep");
    them_tu(&cau1, "trai");
    them_tu(&cau1, "trai");
    them_tu(&cau1, "ok");
    // Tạo danh sách chứa thông tin về số lần xuất hiện của mỗi từ
    listinfor infor;
    list_infor(&infor);
    // Xác định từ xuất hiện nhiều nhất
    Tim_tu_xuat_hien_nhieu_nhat(&cau1, &infor);
    loai_bo_tu_lay(&cau1);
    dem_so_tu_xuat_hien_trong_cau(&cau1);
    return 0;
}
