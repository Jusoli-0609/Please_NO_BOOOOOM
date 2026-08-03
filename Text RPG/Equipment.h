// Equipment.h
#pragma once
#include <string>
#include <vector>

using namespace std;

enum class Equipment_Grade
{
    Empty, 
    Worst, 
    Low, 
    Middle, 
    High, 
    Best 
};

enum class Equipment_Type
{   Engine,     
    Keyboard,         
    Mouse,            
    BlueLight_Glasses, 
    Headset,           
    Empty
};
struct Equipment_Stats
{
    int Attack;
    int Defence;
    int Enhance_Level;
    int Grade_Score;
};

//��� �ڼ��� ����
class Equipment
{
private:
    string _Equipment_Name;//��� �̸�
    int _Attack_Stat;//��� ���ݰ�
    int _Defence_Stat;//��� �⺻ ��
    Equipment_Grade _Grade;//��� ���
    int _Enhance_Level;//��� ��ȭ ����
    int _Equipment_Weight;//��� ����
    string _Equipment_Description;
    Equipment_Type _Equipment_Type;
    string _Equipment__Ascii_Art;

public:
    Equipment();//1.�⺻ ������
    Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade, Equipment_Type type, string art, string description, int weight);//2. ��� �� �� �޴� ������(������ ����ҿ��� �̰ɷ� �밡�� ���Ͽ���)
    int Get_Enhance_Level() const;//3.��ȭ ���� ��ȸ
    void Set_Enhance_Level(int enhance_level);//4.��ȭ ���� ����
    int Get_Attack_Stat() const;//5.��� ���� ���� ��ȸ
    void Set_Attack_Stat(int attack_stat);//6.��� ���� ���� ����
    int Get_Defence_Stat() const;//7. ��� ���� ���� ��ȸ
    void Set_Defence_Stat(int defence_stat);//8. ���� ���� ����
    void Print_Equipment_Info() const;//9.��� ���� ���
    string Get_Equipment_Name() const;//10.��� �̸� ��ȸ
    Equipment_Grade Get_Grade() const;//11. ��� ��� ��ȸ
    string Equipment_Grade_To_String(Equipment_Grade grade) const;//12.��� ��� ���ڿ� �������
    int Get_Equipment_Weight() const;//12. ��� ���� ��ȸ
    void Set_Equipment_Weight(int weight);//13. ��� ���� ����
    string Get_Equipment_Description() const;//14.��� ���� ��ȸ
    void Set_Equipment_Description(string description);//15.��� ���� ����
    void Set_Equipment_Name(string name);//16.��� �̸� ����
    Equipment_Type Get_Equipment_Type() const;// 17. ��� Ÿ�� ��ȸ
    void Set_Equipment_Type(Equipment_Type type);//18. ��� Ÿ�� ����
    string Equipment_Type_To_String(Equipment_Type type) const;//19.��� Ÿ�� ���ڿ���
};

//���� ���â
class Inventory_For_Equipments_Only;
class Currently_Equipped_Equipments
{
    private:
        Equipment _Unreal_Engine_Version;
        Equipment _Keyboard;
        Equipment _Mouse;
        Equipment _BlueLight_Glasses;
        Equipment _Headset;
        //����

        bool Unequip_One_Equipment(Equipment& equipped_item, Inventory_For_Equipments_Only& equipment_inventory, const string& slot_name);

    public:
        Currently_Equipped_Equipments();//1.���� ���� �ִ� ���  ������
        bool Equip_Equipment(const Equipment& equipment);//2.��� ����
        void Print_Currently_Equipped_Equipments() const;//3.���� ��� ���� ���â ��ȸ
        bool Unequip_Equipment_To_Inventory(Inventory_For_Equipments_Only& equipment_inventory );//4.��� ���� 
        int Get_All_Equipments_Grade_Score() const;//5.��ü ��� ����
        Equipment_Stats Get_All_Equipments_Stats() const;//6.��ü ��� ���� ��������
        bool Is_Equipment_Equipped(Equipment_Type type) const;// 7.���� ���� Ȯ��

};

class Inventory_For_Equipments_Only
{
    private:
        vector<Equipment> _Equipments; //��� �����۵��� �����ϴ� ���� ������
        int _Equipment_Current_Count;//���� ���â�� ����ִ� ��� ����
        int _Equipment_Max_Count;//���â �ִ� ���� ���� ����
        int _Equipment_Max_Weight;//���â �� ����
    public:
        Inventory_For_Equipments_Only(); //1. ��� ���� �κ��丮 �⺻ ������
        Inventory_For_Equipments_Only(int max_count, int max_weight); //2. �ִ� ��� ���� ������ ���� ���ϴ� ������
        bool Add_Equipment(const Equipment& equipment); //3. ��� �κ��丮�� �߰��ϴ� �Լ�
        void Print_Equipment_Inventory() const; //4. ���� ��� �κ��丮�� ����ִ� ��� ��� ���
        int Get_Equipment_Current_Count() const; //5. ���� ���� ���� ��� ���� ��ȸ
        int Get_Equipment_Max_Count() const; //6. �ִ� ���� ������ ��� ���� ��ȸ
        Equipment Get_Equipment_By_Index(int index) const; //7. �ε��� ��ȣ�� Ư�� ��� ��ȸ
        void Throw_Away_Equipment(); //8. ��� �κ��丮���� ������ ��� ������
        void Increase_Equipment_Max_Count(int increase_count); //9. ��� �κ��丮 �ִ� ���� ĭ ����
        void Sort_Equipment_Inventory();//10.���� 
        void Change_Equipment_Inventory_Order();//11.���� ����
        void Equip_Equipment_From_Inventory(Currently_Equipped_Equipments& equipped);//12.��� �����Ű��
        int Get_Total_Equipment_Weight() const;//�ѹ���
};