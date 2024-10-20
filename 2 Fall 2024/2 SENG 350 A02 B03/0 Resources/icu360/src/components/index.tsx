"use client"
import { Metadata } from 'next'
import { useState } from 'react'
import { Card, CardContent, CardFooter, CardHeader, CardTitle } from "@/components/ui/card"
import { Button } from "@/components/ui/button"
import { Navbar } from "@/components/navbar"
import { Menu } from 'lucide-react'
import { PatientRecord } from "@/utils/types"

export const metadata: Metadata = {
    title: 'My HealthApp | Overview',
    description: 'Overview of your health data',
}

// async function getData(): Promise<PatientRecord> {
//     const res = await fetch("")
//     if (!res.ok) { throw new Error('Failed to fetch data') }
//     return res.json()
// }

function SingleCard({ title, content }: Readonly<{ title?: string; content?: string }>) {
    return (
        <Card>
            <CardHeader>
                <CardTitle>{title}</CardTitle>
            </CardHeader>
            <CardContent>
                <p>{content}</p>
            </CardContent>
            <CardFooter>
                <Button>View Details</Button>
            </CardFooter>
        </Card>
    )
}

function MainContent() {
    return (
        <>
            <h2 className="text-2xl font-bold mt-5 text-blue-600">Frequently Accessed</h2>
            <div className="grid grid-cols-1 md:grid-cols-3 lg:grid-cols-3 gap-6 mt-6">
                <SingleCard
                    title="Medications"
                    content="View your current and past medications."
                />
                <SingleCard
                    title="Hospital Visits"
                    content="View your hospital visits and reports."
                />
                <SingleCard
                    title="Clinician Visits"
                    content="View your past clinic visits and records."
                />
            </div>

            <h2 className="text-2xl font-bold mt-10 text-blue-600">Recently Accessed</h2>
            <div className="grid grid-cols-1 md:grid-cols-3 lg:grid-cols-3 gap-6 mt-6">
                <SingleCard
                    title="Immunizations"
                    content="View your immunization records."
                />
                <SingleCard
                    title="Insurance"
                    content="View your insurance information"
                />
                <SingleCard
                    title="Lab Results"
                    content="View your lab results."
                />
                <SingleCard
                    title="Advanced Care Planning"
                    content="View and update your advance care planning preferences."
                />
            </div>
        </>
    )
}

export default function Overview() {
    const [isNavbarVisible, setIsNavbarVisible] = useState(false)

    const toggleNavbar = () => setIsNavbarVisible(!isNavbarVisible)

    return (
        <div className="flex h-screen overflow-hidden">
            <div
                className={`fixed inset-y-0 left-0 transform ${isNavbarVisible ? 'translate-x-0' : '-translate-x-full'
                    } md:relative md:translate-x-0 transition duration-200 ease-in-out z-30`}
            >
                <Navbar name="John Doe" tab="Tab 1" />
            </div>
            <div className="flex-1 overflow-auto relative">
                <Button
                    variant="outline"
                    size="icon"
                    className="fixed top-4 left-4 z-40 md:hidden"
                    onClick={toggleNavbar}
                    aria-label={isNavbarVisible ? "Close menu" : "Open menu"}
                >
                    <Menu className="h-4 w-4" />
                </Button>
                <main className="p-6 pt-16 md:pt-6">
                    <div className="flex items-center">
                        <h1 className="text-3xl font-bold">
                            My <span className="text-primary">Overview</span>
                        </h1>
                    </div>
                    <p className="text-lg mt-2">Find access to all of your health data here.</p>
                    <hr className="my-6" />
                    <MainContent />
                </main>
            </div>
        </div>
    )
}