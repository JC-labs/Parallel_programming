package j;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Math {
    private Integer n;
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public Math() {
        System.out.print("Enter N for all the vectors an matrices: ");
        n = read_integer();
    }

    public class Vector {
        Double[] m_data;
        public Vector() {
            m_data = new Double[n];
            for (int i = 0; i < n; i++)
                m_data[i] = 0.0;
        }
        void set(Integer i, Double v) {
            m_data[i] = v;
        }
        void append(Integer i, Double v) {
            m_data[i] += v;
        }
        Double get(Integer i) {
            return m_data[i];
        }
    }
    public class Matrix {
        Double[][] m_data;
        public Matrix() {
            m_data = new Double[n][n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    m_data[i][j] = 0.0;
        }/*
        Matrix multiply(Matrix m) {
            Matrix ret = new Matrix();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        ret.m_data[i][j] += m_data[i][k] * m.m_data[k][j];
            return ret;
        }
        void swap(Integer i, Integer j) {
            Double t = m_data[i][j];
            m_data[i][j] = m_data[j][i];
            m_data[j][i] = m_data[i][j];
        }
        Matrix transpose() {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < i; j++)
                    swap(i, j);
            return this;
        }*/
        void set(Integer i, Integer j, Double v) {
            m_data[i][j] = v;
        }
        Double get(Integer i, Integer j) {
            return m_data[i][j];
        }
    }

	public int getN() { return n; }
	
    public Integer read_integer() {
        try {
            return Integer.parseInt(reader.readLine());
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
    public Double read_double() {
        try{
            return Double.parseDouble(reader.readLine());
        } catch (IOException e) {
            e.printStackTrace();
            return -1.0;
        }
    }
    public Vector read_vector() {
        Vector ret = new Vector();
        for (int i = 0; i < n; i++)
            ret.set(i, read_double());
        return ret;
    }
    public Matrix read_matrix() {
        Matrix ret = new Matrix();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ret.set(i, j, read_double());
        return ret;
    }

    public Vector fill_vector(Double value) {
        Vector ret = new Vector();
        for (int i = 0; i < n; i++)
            ret.set(i, value);
        return ret;
    }
    public Matrix fill_matrix(Double value) {
        Matrix ret = new Matrix();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ret.set(i, j, value);
        return ret;
    }
    public void print(Vector v) {
        for (int i = 0; i < n && n <= 10; i++)
            System.out.print(v.get(i).toString() + " ");
        System.out.println("");
    }
    public void print(Matrix m) {
        for (int i = 0; i < n && n <= 10; i++) {
            for (int j = 0; j < n && n <= 10; j++)
                System.out.print(m.get(i, j).toString() + " ");
            System.out.println("");
        }
        System.out.println("");
    }
}
