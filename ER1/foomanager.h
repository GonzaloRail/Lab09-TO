#ifndef FOOMANAGER_H
#define FOOMANAGER_H

class FooManager {
public:
    // Devuelve el valor de SampleData
    int GetSampleData() {
        return SampleData;
    }

    // Crea la instancia única del Singleton
    static void Create() {
        if (m_Inst == nullptr) {
            m_Inst = new FooManager();
        }
    }

    // Devuelve la instancia única
    static FooManager* GetInst() {
        return m_Inst;
    }

    // Libera la instancia única
    static void Destroy() {
        delete m_Inst;
        m_Inst = nullptr;
    }

protected:
    // Constructor y destructor protegidos para evitar instanciación directa
    FooManager();
    virtual ~FooManager();

private:
    int SampleData; // Dato de ejemplo
    static FooManager* m_Inst; // Instancia única
};

#endif // FOOMANAGER_H
