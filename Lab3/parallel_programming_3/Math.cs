using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace parallel_programming_3
{
    class Math
    {
        static private Int32 n;

        public Math()
        {
            Console.Write("Enter N for all the vectors an matrices: ");
            n = read_Int32eger();
        }

        public class Vector
        {
            Double[] m_data;
            public Vector()
            {
                m_data = new Double[n];
                for (Int32 i = 0; i < n; i++)
                    m_data[i] = 0.0;
            }
            public Vector sort()
            {
                Array.Sort(m_data);
                return this;
            }
            public Vector multiply(Matrix m)
            {
                Vector ret = new Vector();
                for (Int32 i = 0; i < n; i++)
                    for (Int32 j = 0; j < n; j++)
                        ret.m_data[i] += m_data[j] * m.get(j, i);
                return ret;
            }
            public Vector sum(Vector v)
            {
                Vector ret = new Vector();
                for (Int32 i = 0; i < n; i++)
                    ret.m_data[i] = m_data[i] + v.m_data[i];
                return ret;
            }
            public void set(Int32 i, Double v)
            {
                m_data[i] = v;
            }
            public Double get(Int32 i)
            {
                return m_data[i];
            }
        }
        public class Matrix
        {
            Double[,] m_data;
            public Matrix()
            {
                m_data = new Double[n, n];
                for (Int32 i = 0; i < n; i++)
                    for (Int32 j = 0; j < n; j++)
                        m_data[i, j] = 0.0;
            }
            public Matrix multiply(Matrix m)
            {
                Matrix ret = new Matrix();
                for (Int32 i = 0; i < n; i++)
                    for (Int32 j = 0; j < n; j++)
                        for (Int32 k = 0; k < n; k++)
                            ret.m_data[i, j] += m_data[i, k] * m.m_data[k, j];
                return ret;
            }
            public void swap(Int32 i, Int32 j)
            {
                Double t = m_data[i, j];
                m_data[i, j] = m_data[j, i];
                m_data[j, i] = m_data[i, j];
            }
            public Matrix transpose()
            {
                for (Int32 i = 0; i < n; i++)
                    for (Int32 j = 0; j < i; j++)
                        swap(i, j);
                return this;
            }
            public void set(Int32 i, Int32 j, Double v)
            {
                m_data[i, j] = v;
            }
            public Double get(Int32 i, Int32 j)
            {
                return m_data[i, j];
            }
        }

        public Int32 read_Int32eger()
        {
            return Int32.Parse(Console.ReadLine());
        }
        public Double read_double()
        {
            return Double.Parse(Console.ReadLine());
        }
        public Vector read_vector()
        {
            Vector ret = new Vector();
            for (Int32 i = 0; i < n; i++)
                ret.set(i, read_double());
            return ret;
        }
        public Matrix read_matrix()
        {
            Matrix ret = new Matrix();
            for (Int32 i = 0; i < n; i++)
                for (Int32 j = 0; j < n; j++)
                    ret.set(i, j, read_double());
            return ret;
        }

        public Vector fill_vector(Double value)
        {
            Vector ret = new Vector();
            for (Int32 i = 0; i < n; i++)
                ret.set(i, value);
            return ret;
        }
        public Matrix fill_matrix(Double value)
        {
            Matrix ret = new Matrix();
            for (Int32 i = 0; i < n; i++)
                for (Int32 j = 0; j < n; j++)
                    ret.set(i, j, value);
            return ret;
        }
        public void print(Vector v)
        {
            for (Int32 i = 0; i < n && n <= 10; i++)
                Console.Write(v.get(i).ToString() + " ");
            Console.WriteLine();
        }
        public void print(Matrix m)
        {
            for (Int32 i = 0; i < n && n <= 10; i++)
            {
                for (Int32 j = 0; j < n && n <= 10; j++)
                    Console.Write(m.get(i, j).ToString() + " ");
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        public Vector function_1(Vector a, Vector b, Matrix ma, Matrix me)
        {
            return a.sort().multiply(ma.multiply(me)).sum(b.sort());
        }
        public Matrix function_2(Matrix mk, Matrix mh, Matrix mf)
        {
            return mk.transpose().multiply(mh.multiply(mf));
        }
        public Vector function_3(Vector r, Vector s, Matrix mt, Matrix mp)
        {
            return r.sum(s).sort().multiply(mt.multiply(mp));
        }
    }
};